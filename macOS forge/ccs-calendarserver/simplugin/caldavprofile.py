##
# Copyright (c) 2011-2017 Apple Inc. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
##

"""
Implementation of specific end-user behaviors.
"""

from __future__ import division

import json
import sys
from uuid import uuid4

from caldavclientlibrary.protocol.caldav.definitions import caldavxml

from twisted.python import context
from twisted.python.log import msg
from twisted.python.failure import Failure
from twisted.internet.defer import Deferred, succeed, inlineCallbacks, returnValue
from twisted.internet.task import LoopingCall
from twisted.web.http import PRECONDITION_FAILED

from twistedcaldav.ical import Property, Component

from clientsim.framework.stats import NearFutureDistribution, NormalDistribution, UniformDiscreteDistribution, mean, median
from clientsim.framework.stats import LogNormalDistribution, RecurrenceDistribution
from clientsim.framework.logger import SummarizingMixin
from clientsim.framework.baseclient import IncorrectResponseCode
from clientsim.framework.baseprofile import BaseProfile as SuperBaseProfile, loopWithDistribution
from simplugin.caldavclient import Calendar

from pycalendar.datetime import DateTime
from pycalendar.duration import Duration

from datetime import datetime


class BaseProfile(SuperBaseProfile):

    def _calendarsOfType(self, calendarType, componentType, justOwned=False):
        results = []

        for cal in self._client._calendars.itervalues():
            if cal.resourceType == calendarType and componentType in cal.componentTypes:
                if justOwned:
                    if (not cal.shared) or cal.sharedByMe:
                        results.append(cal)
                else:
                    results.append(cal)

        return results

    def _getRandomCalendarOfType(self, componentType, justOwned=False):
        """
        Return a random L{Calendar} object from the current user
        or C{None} if there are no calendars to work with
        """
        calendars = self._calendarsOfType(caldavxml.calendar, componentType, justOwned=justOwned)
        if not calendars:
            return None
        # Choose a random calendar
        calendar = self.random.choice(calendars)
        return calendar

    def _getRandomEventOfType(self, componentType, justOwned=True):
        """
        Return a random L{Event} object from the current user
        or C{None} if there are no events to work with
        """
        calendars = self._calendarsOfType(caldavxml.calendar, componentType, justOwned=justOwned)
        while calendars:
            calendar = self.random.choice(calendars)
            calendars.remove(calendar)
            if not calendar.events:
                continue

            events = calendar.events.keys()
            while events:
                href = self.random.choice(events)
                events.remove(href)
                event = calendar.events[href]
                if not event.component:
                    continue
                if event.scheduleTag:
                    continue

                return event
        return None

    def _isSelfAttendee(self, attendee):
        """
        Try to match one of the attendee's identifiers against one of
        C{self._client}'s identifiers.  Return C{True} if something matches,
        C{False} otherwise.
        """
        return attendee.parameterValue('EMAIL') == self._client.email[len('mailto:'):]

    def _newOperation(self, label, deferred):
        """
        Helper to emit a log event when a new operation is started and
        another one when it completes.
        """
        # If this is a scheduled request, record the lag in the
        # scheduling now so it can be reported when the response is
        # received.
        lag = context.get('lag', None)

        before = self._reactor.seconds()
        msg(
            type="operation",
            phase="start",
            user=self._client.record.uid,
            client_type=self._client.title,
            client_id=self._client._client_id,
            label=label,
            lag=lag,
        )

        def finished(passthrough):
            success = not isinstance(passthrough, Failure)
            if not success:
                passthrough.trap(IncorrectResponseCode)
                passthrough = passthrough.value.response
            after = self._reactor.seconds()
            msg(
                type="operation",
                phase="end",
                duration=after - before,
                user=self._client.record.uid,
                client_type=self._client.title,
                client_id=self._client._client_id,
                label=label,
                success=success,
            )
            return passthrough
        deferred.addBoth(finished)
        return deferred

    def _failedOperation(self, label, reason):
        """
        Helper to emit a log event when an operation fails.
        """
        msg(
            type="operation",
            phase="failed",
            user=self._client.record.uid,
            client_type=self._client.title,
            client_id=self._client._client_id,
            label=label,
            reason=reason,
        )
        self._sim._simFailure("%s: %s" % (label, reason,), self._reactor)


class CannotAddAttendee(Exception):
    """
    Indicates no new attendees can be invited to a particular event.
    """
    pass


class Inviter(BaseProfile):
    """
    A Calendar user who invites other users to new events.
    """
    _eventTemplate = Component.fromString("""\
BEGIN:VCALENDAR
VERSION:2.0
PRODID:-//Apple Inc.//iCal 4.0.3//EN
CALSCALE:GREGORIAN
BEGIN:VEVENT
CREATED:20101018T155431Z
UID:C98AD237-55AD-4F7D-9009-0D355D835822
DTEND;TZID=America/New_York:20101021T130000
TRANSP:OPAQUE
SUMMARY:Simple event
DTSTART;TZID=America/New_York:20101021T120000
DTSTAMP:20101018T155438Z
SEQUENCE:2
END:VEVENT
END:VCALENDAR
""".replace("\n", "\r\n"))

    def setParameters(
        self,
        enabled=True,
        sendInvitationDistribution=NormalDistribution(600, 60),
        inviteeDistribution=UniformDiscreteDistribution(range(-10, 11)),
        inviteeClumping=True,
        inviteeCountDistribution=LogNormalDistribution(1.2, 1.2),
        eventStartDistribution=NearFutureDistribution(),
        eventDurationDistribution=UniformDiscreteDistribution([
            15 * 60, 30 * 60,
            45 * 60, 60 * 60,
            120 * 60
        ]),
        recurrenceDistribution=RecurrenceDistribution(False),
    ):
        self.enabled = enabled
        self._sendInvitationDistribution = sendInvitationDistribution
        self._inviteeDistribution = inviteeDistribution
        self._inviteeClumping = inviteeClumping
        self._inviteeCountDistribution = inviteeCountDistribution
        self._eventStartDistribution = eventStartDistribution
        self._eventDurationDistribution = eventDurationDistribution
        self._recurrenceDistribution = recurrenceDistribution

    def run(self):
        return loopWithDistribution(
            self._reactor, self._sendInvitationDistribution, self._invite)

    def _addAttendee(self, event, attendees):
        """
        Create a new attendee to add to the list of attendees for the
        given event.
        """
        selfRecord = self._sim.getUserRecord(self._number)
        invitees = set([u'mailto:%s' % (selfRecord.email,)])
        for att in attendees:
            invitees.add(att.value())

        for _ignore_i in range(10):

            sample = self._inviteeDistribution.sample()
            if self._inviteeClumping:
                sample = self._number + sample
            invitee = max(0, sample)

            try:
                record = self._sim.getUserRecord(invitee)
            except IndexError:
                continue
            cuaddr = u'mailto:%s' % (record.email,)
            if cuaddr not in invitees:
                break
        else:
            raise CannotAddAttendee("Can't find uninvited user to invite.")

        attendee = Property(
            name=u'ATTENDEE',
            value=cuaddr.encode("utf-8"),
            params={
                'CN': record.commonName,
                'CUTYPE': 'INDIVIDUAL',
                'PARTSTAT': 'NEEDS-ACTION',
                'ROLE': 'REQ-PARTICIPANT',
                'RSVP': 'TRUE',
            },
        )

        event.addProperty(attendee)
        attendees.append(attendee)

    def _invite(self):
        """
        Try to add a new event, or perhaps remove an
        existing attendee from an event.

        @return: C{None} if there are no events to play with,
            otherwise a L{Deferred} which fires when the attendee
            change has been made.
        """

        if not self._client.started:
            return succeed(None)

        # Find calendars which are eligible for invites
        calendars = self._calendarsOfType(caldavxml.calendar, "VEVENT")

        while calendars:
            # Pick one at random from which to try to create an event
            # to modify.
            calendar = self.random.choice(calendars)
            calendars.remove(calendar)

            # Copy the template event and fill in some of its fields
            # to make a new event to create on the calendar.
            vcalendar = self._eventTemplate.duplicate()
            vevent = vcalendar.mainComponent()
            uid = str(uuid4())
            dtstart = self._eventStartDistribution.sample()
            dtend = dtstart + Duration(seconds=self._eventDurationDistribution.sample())
            vevent.replaceProperty(Property("CREATED", DateTime.getNowUTC()))
            vevent.replaceProperty(Property("DTSTAMP", DateTime.getNowUTC()))
            vevent.replaceProperty(Property("DTSTART", dtstart))
            vevent.replaceProperty(Property("DTEND", dtend))
            vevent.replaceProperty(Property("UID", uid))

            rrule = self._recurrenceDistribution.sample()
            if rrule is not None:
                vevent.addProperty(Property(None, None, None, pycalendar=rrule))

            vevent.addProperty(self._client._makeSelfOrganizer())
            vevent.addProperty(self._client._makeSelfAttendee())

            attendees = list(vevent.properties('ATTENDEE'))
            for _ignore in range(int(self._inviteeCountDistribution.sample())):
                try:
                    self._addAttendee(vevent, attendees)
                except CannotAddAttendee:
                    continue

            href = '%s%s.ics' % (calendar.url, uid)
            d = self._client.addInvite(href, vcalendar)
            return self._newOperation("invite", d)


class Accepter(BaseProfile):
    """
    A Calendar user who accepts invitations to events. As well as accepting requests, this
    will also remove cancels and replies.
    """

    def setParameters(
        self,
        enabled=True,
        acceptDelayDistribution=NormalDistribution(1200, 60)
    ):
        self.enabled = enabled
        self._accepting = set()
        self._acceptDelayDistribution = acceptDelayDistribution

    def run(self):
        self._subscription = self._client.catalog["eventChanged"].subscribe(self.eventChanged)
        # TODO: Propagate errors from eventChanged and _acceptInvitation to this Deferred
        return Deferred()

    def eventChanged(self, href):
        # Just respond to normal calendar events
        calendar = href.rsplit('/', 1)[0] + '/'
        try:
            calendar = self._client._calendars[calendar]
        except KeyError:
            return

        if calendar.resourceType == caldavxml.schedule_inbox:
            # Handle inbox differently
            self.inboxEventChanged(calendar, href)
        elif calendar.resourceType == caldavxml.calendar:
            self.calendarEventChanged(calendar, href)
        else:
            return

    def calendarEventChanged(self, calendar, href):
        if href in self._accepting:
            return

        component = self._client._events[href].component
        # Check to see if this user is in the attendee list in the
        # NEEDS-ACTION PARTSTAT.
        attendees = tuple(component.mainComponent().properties('ATTENDEE'))
        for attendee in attendees:
            if self._isSelfAttendee(attendee):
                if attendee.parameterValue('PARTSTAT') == 'NEEDS-ACTION':
                    delay = self._acceptDelayDistribution.sample()
                    self._accepting.add(href)
                    self._reactor.callLater(
                        delay, self._acceptInvitation, href, attendee)

    def inboxEventChanged(self, calendar, href):
        if href in self._accepting:
            return

        component = self._client._events[href].component
        method = component.propertyValue('METHOD')
        if method == "REPLY":
            # Replies are immediately deleted
            self._accepting.add(href)
            self._reactor.callLater(
                0, self._handleReply, href)

        elif method == "CANCEL":
            # Cancels are handled after a user delay
            delay = self._acceptDelayDistribution.sample()
            self._accepting.add(href)
            self._reactor.callLater(
                delay, self._handleCancel, href)

    def _acceptInvitation(self, href, attendee):
        def change():
            accepted = self._makeAcceptedAttendee(attendee)
            return self._client.changeEventAttendee(href, attendee, accepted)
        d = change()

        def scheduleError(reason):
            reason.trap(IncorrectResponseCode)
            if reason.value.response.code != PRECONDITION_FAILED:
                return reason.value.response.code

            # Download the event again and attempt to make the change
            # to the attendee list again.
            d = self._client.updateEvent(href)

            def cbUpdated(ignored):
                d = change()
                d.addErrback(scheduleError)
                return d
            d.addCallback(cbUpdated)
            return d
        d.addErrback(scheduleError)

        def accepted(ignored):
            # Find the corresponding event in the inbox and delete it.
            uid = self._client._events[href].getUID()
            for cal in self._client._calendars.itervalues():
                if cal.resourceType == caldavxml.schedule_inbox:
                    for event in cal.events.itervalues():
                        if uid == event.getUID():
                            return self._client.deleteEvent(event.url)
        d.addCallback(accepted)

        def finished(passthrough):
            self._accepting.remove(href)
            return passthrough
        d.addBoth(finished)
        return self._newOperation("accept", d)

    def _handleReply(self, href):
        d = self._client.deleteEvent(href)
        d.addBoth(self._finishRemoveAccepting, href)
        return self._newOperation("reply done", d)

    def _finishRemoveAccepting(self, passthrough, href):
        self._accepting.remove(href)
        if isinstance(passthrough, Failure):
            passthrough.trap(IncorrectResponseCode)
            passthrough = passthrough.value.response
        return passthrough

    def _handleCancel(self, href):

        uid = self._client._events[href].getUID()
        d = self._client.deleteEvent(href)

        def removed(ignored):
            # Find the corresponding event in any calendar and delete it.
            for cal in self._client._calendars.itervalues():
                if cal.resourceType == caldavxml.calendar:
                    for event in cal.events.itervalues():
                        if uid == event.getUID():
                            return self._client.deleteEvent(event.url)
        d.addCallback(removed)
        d.addBoth(self._finishRemoveAccepting, href)
        return self._newOperation("cancelled", d)

    def _makeAcceptedAttendee(self, attendee):
        accepted = attendee.duplicate()
        accepted.setParameter('PARTSTAT', 'ACCEPTED')
        accepted.removeParameter('RSVP')
        return accepted


class AttachmentDownloader(BaseProfile):
    """
    A Calendar user who downloads attachments.
    """

    def setParameters(
        self,
        enabled=True,
    ):
        self.enabled = enabled

    def run(self):
        self._subscription = self._client.catalog["eventChanged"].subscribe(self.eventChanged)
        return Deferred()

    def eventChanged(self, href):
        # Just respond to normal calendar events
        calendar = href.rsplit('/', 1)[0] + '/'
        try:
            calendar = self._client._calendars[calendar]
        except KeyError:
            return

        if calendar.resourceType == caldavxml.calendar:
            self.calendarEventChanged(calendar, href)

    def calendarEventChanged(self, calendar, href):
        component = self._client._events[href].component
        attachments = tuple(component.mainComponent().properties('ATTACH'))
        if attachments:
            for attachment in attachments:
                attachmentHref = attachment.value()
                managedId = attachment.parameterValue('MANAGED-ID')
                self._reactor.callLater(
                    0, self._client.getAttachment, attachmentHref, managedId
                )


class Eventer(BaseProfile):
    """
    A Calendar user who creates new events.
    """
    _eventTemplate = Component.fromString("""\
BEGIN:VCALENDAR
VERSION:2.0
PRODID:-//Apple Inc.//iCal 4.0.3//EN
CALSCALE:GREGORIAN
BEGIN:VEVENT
CREATED:20101018T155431Z
UID:C98AD237-55AD-4F7D-9009-0D355D835822
DTEND;TZID=America/New_York:20101021T130000
TRANSP:OPAQUE
SUMMARY:Simple event
DTSTART;TZID=America/New_York:20101021T120000
DTSTAMP:20101018T155438Z
SEQUENCE:2
END:VEVENT
END:VCALENDAR
""".replace("\n", "\r\n"))

    def setParameters(
        self,
        enabled=True,
        interval=25,
        eventStartDistribution=NearFutureDistribution(),
        eventDurationDistribution=UniformDiscreteDistribution([
            15 * 60, 30 * 60,
            45 * 60, 60 * 60,
            120 * 60
        ]),
        recurrenceDistribution=RecurrenceDistribution(False),
    ):
        self.enabled = enabled
        self._interval = interval
        self._eventStartDistribution = eventStartDistribution
        self._eventDurationDistribution = eventDurationDistribution
        self._recurrenceDistribution = recurrenceDistribution

    def run(self):
        self._call = LoopingCall(self._addEvent)
        self._call.clock = self._reactor
        return self._call.start(self._interval)

    def _addEvent(self):
        # Don't perform any operations until the client is up and running
        if not self._client.started:
            return succeed(None)

        calendar = self._getRandomCalendarOfType('VEVENT')

        if not calendar:
            # No VEVENT calendars, so no new event...
            return succeed(None)

        # Copy the template event and fill in some of its fields
        # to make a new event to create on the calendar.
        vcalendar = self._eventTemplate.duplicate()
        vevent = vcalendar.mainComponent()
        uid = str(uuid4())
        dtstart = self._eventStartDistribution.sample()
        dtend = dtstart + Duration(seconds=self._eventDurationDistribution.sample())
        vevent.replaceProperty(Property("CREATED", DateTime.getNowUTC()))
        vevent.replaceProperty(Property("DTSTAMP", DateTime.getNowUTC()))
        vevent.replaceProperty(Property("DTSTART", dtstart))
        vevent.replaceProperty(Property("DTEND", dtend))
        vevent.replaceProperty(Property("UID", uid))

        rrule = self._recurrenceDistribution.sample()
        if rrule is not None:
            vevent.addProperty(Property(None, None, None, pycalendar=rrule))

        href = '%s%s.ics' % (calendar.url, uid)
        d = self._client.addEvent(href, vcalendar)
        return self._newOperation("create", d)


class EventUpdaterBase(BaseProfile):

    @inlineCallbacks
    def action(self):
        # Don't perform any operations until the client is up and running
        if not self._client.started:
            returnValue(None)

        event = self._getRandomEventOfType('VEVENT', justOwned=True)
        if not event:
            returnValue(None)
        component = event.component
        vevent = component.mainComponent()

        label = yield self.modifyEvent(event.url, vevent)
        if label:
            vevent.replaceProperty(Property("DTSTAMP", DateTime.getNowUTC()))

            event.component = component
            yield self._newOperation(
                label,
                self._client.changeEvent(event.url)
            )

    def run(self):
        self._call = LoopingCall(self.action)
        self._call.clock = self._reactor
        return self._call.start(self._interval)

    def modifyEvent(self, href, vevent):
        """Overridden by subclasses"""
        pass


class TitleChanger(EventUpdaterBase):

    def setParameters(
        self,
        enabled=True,
        interval=60,
        titleLengthDistribution=NormalDistribution(10, 2)
    ):
        self.enabled = enabled
        self._interval = interval
        self._titleLength = titleLengthDistribution

    def modifyEvent(self, _ignore_href, vevent):
        length = max(5, int(self._titleLength.sample()))
        vevent.replaceProperty(Property("SUMMARY", "Event" + "." * (length - 5)))
        return succeed("update{title}")


class DescriptionChanger(EventUpdaterBase):

    def setParameters(
        self,
        enabled=True,
        interval=60,
        descriptionLengthDistribution=NormalDistribution(10, 2)
    ):
        self.enabled = enabled
        self._interval = interval
        self._descriptionLength = descriptionLengthDistribution

    def modifyEvent(self, _ignore_href, vevent):
        length = int(self._descriptionLength.sample())
        vevent.replaceProperty(Property("DESCRIPTION", "." * length))
        return succeed("update{description}")


class Attacher(EventUpdaterBase):

    def setParameters(
        self,
        enabled=True,
        interval=60,
        fileSizeDistribution=NormalDistribution(1024, 1),
    ):
        self.enabled = enabled
        self._interval = interval
        self._fileSize = fileSizeDistribution

    @inlineCallbacks
    def modifyEvent(self, href, vevent):
        fileSize = int(self._fileSize.sample())
        yield self._client.postAttachment(href, 'x' * fileSize)
        returnValue(None)


class EventCountLimiter(EventUpdaterBase):
    """
    Examines the number of events in each calendar collection, and when that
    count exceeds eventCountLimit, events are randomly removed until the count
    falls back to the limit.
    """

    def setParameters(
        self,
        enabled=True,
        interval=60,
        eventCountLimit=1000
    ):
        self.enabled = enabled
        self._interval = interval
        self._limit = eventCountLimit

    @inlineCallbacks
    def action(self):
        # Don't perform any operations until the client is up and running
        if not self._client.started:
            returnValue(None)

        for calendar in self._calendarsOfType(caldavxml.calendar, "VEVENT", justOwned=True):
            while len(calendar.events) > self._limit:
                event = calendar.events[self.random.choice(calendar.events.keys())]
                yield self._client.deleteEvent(event.url)


class CalendarSharer(BaseProfile):
    """
    A Calendar user who shares calendars to other random users.
    """

    def setParameters(
        self,
        enabled=True,
        interval=60
    ):
        self.enabled = enabled
        self._interval = interval

    def run(self):
        self._call = LoopingCall(self.action)
        self._call.clock = self._reactor
        return self._call.start(self._interval)

    @inlineCallbacks
    def action(self):
        # Don't perform any operations until the client is up and running
        if not self._client.started:
            returnValue(None)

        yield self.shareCalendar()

    @inlineCallbacks
    def shareCalendar(self):

        # pick a calendar
        calendar = self._getRandomCalendarOfType('VEVENT', justOwned=True)
        if not calendar:
            returnValue(None)

        # pick a random sharee
        shareeRecord = self._sim.getRandomUserRecord(besides=self._number)
        if shareeRecord is None:
            returnValue(None)

        # POST the sharing invite
        mailto = "mailto:{}".format(shareeRecord.email)
        body = Calendar.addInviteeXML(mailto, calendar.name, readwrite=True)
        yield self._client.postXML(
            calendar.url,
            body,
            label="POST{share-calendar}"
        )


class AlarmAcknowledger(BaseProfile):
    """
    A Calendar user who creates a new event, and then updates its alarm.
    """
    _eventTemplate = Component.fromString("""\
BEGIN:VCALENDAR
VERSION:2.0
PRODID:-//Apple Inc.//iCal 4.0.3//EN
CALSCALE:GREGORIAN
BEGIN:VEVENT
CREATED:20101018T155431Z
UID:C98AD237-55AD-4F7D-9009-0D355D835822
DTEND;TZID=America/New_York:20101021T130000
TRANSP:OPAQUE
SUMMARY:Simple event
DTSTART;TZID=America/New_York:20101021T120000
DTSTAMP:20101018T155438Z
SEQUENCE:2
BEGIN:VALARM
X-WR-ALARMUID:D9D1AC84-F629-4B9D-9B6B-4A6CA9A11FEF
UID:D9D1AC84-F629-4B9D-9B6B-4A6CA9A11FEF
DESCRIPTION:Event reminder
TRIGGER:-PT8M
ACTION:DISPLAY
END:VALARM
END:VEVENT
END:VCALENDAR
""".replace("\n", "\r\n"))

    def setParameters(
        self,
        enabled=True,
        interval=5,
        pastTheHour=[0, 15, 30, 45],
        eventStartDistribution=NearFutureDistribution(),
        eventDurationDistribution=UniformDiscreteDistribution([
            15 * 60, 30 * 60,
            45 * 60, 60 * 60,
            120 * 60
        ]),
        recurrenceDistribution=RecurrenceDistribution(False),
    ):
        self.enabled = enabled
        self._interval = interval
        self._pastTheHour = pastTheHour
        self._eventStartDistribution = eventStartDistribution
        self._eventDurationDistribution = eventDurationDistribution
        self._recurrenceDistribution = recurrenceDistribution
        self._lastMinuteChecked = -1

    def initialize(self):
        """
        Called before the profile runs for real. Can be used to initialize client state.

        @return: a L{Deferred} that fires when initialization is done
        """

        return self._initEvent()

    def run(self):
        self._call = LoopingCall(self._updateEvent)
        self._call.clock = self._reactor
        return self._call.start(self._interval)

    def _initEvent(self):
        # Don't perform any operations until the client is up and running
        if not self._client.started:
            return succeed(None)

        # If it already exists, don't re-create
        calendar = self._calendarsOfType(caldavxml.calendar, "VEVENT")[0]
        if calendar.events:
            events = [event for event in calendar.events.values() if event.url.endswith("event_to_update.ics")]
            if events:
                return succeed(None)

        # Copy the template event and fill in some of its fields
        # to make a new event to create on the calendar.
        vcalendar = self._eventTemplate.duplicate()
        vevent = vcalendar.mainComponent()
        uid = str(uuid4())
        dtstart = self._eventStartDistribution.sample()
        dtend = dtstart + Duration(seconds=self._eventDurationDistribution.sample())
        vevent.replaceProperty(Property("CREATED", DateTime.getNowUTC()))
        vevent.replaceProperty(Property("DTSTAMP", DateTime.getNowUTC()))
        vevent.replaceProperty(Property("DTSTART", dtstart))
        vevent.replaceProperty(Property("DTEND", dtend))
        vevent.replaceProperty(Property("UID", uid))

        rrule = self._recurrenceDistribution.sample()
        if rrule is not None:
            vevent.addProperty(Property(None, None, None, pycalendar=rrule))

        href = '%s%s' % (calendar.url, "event_to_update.ics")
        d = self._client.addEvent(href, vcalendar)
        return self._newOperation("create", d)

    def _shouldUpdate(self, minutePastTheHour):
        """
        We want to only acknowledge our alarm at the "past the hour" minutes
        we've been configured for.
        """
        should = False
        if minutePastTheHour in self._pastTheHour:
            # This is one of the minutes we should update on, but only update
            # as we pass into this minute, and not subsequent times
            if minutePastTheHour != self._lastMinuteChecked:
                should = True

        self._lastMinuteChecked = minutePastTheHour
        return should

    def _updateEvent(self):
        """
        Set the ACKNOWLEDGED property on an event.

        @return: C{None} if there are no events to play with,
            otherwise a L{Deferred} which fires when the acknowledged
            change has been made.
        """

        # Only do updates when we reach of the designated minutes past the hour
        if not self._shouldUpdate(datetime.now().minute):
            return succeed(None)

        if not self._client.started:
            return succeed(None)

        # If it does not exist, try to create it
        calendar = self._calendarsOfType(caldavxml.calendar, "VEVENT")[0]
        if not calendar.events:
            return self._initEvent()
        events = [event for event in calendar.events.values() if event.url.endswith("event_to_update.ics")]
        if not events:
            return self._initEvent()
        event = events[0]

        # Add/update the ACKNOWLEDGED property
        component = event.component.mainComponent()
        component.replaceProperty(Property("ACKNOWLEDGED", DateTime.getNowUTC()))
        d = self._client.changeEvent(event.url)
        return self._newOperation("update", d)


class Tasker(BaseProfile):
    """
    A Calendar user who creates new tasks.
    """
    _taskTemplate = Component.fromString("""\
BEGIN:VCALENDAR
VERSION:2.0
PRODID:-//Apple Inc.//iCal 4.0.3//EN
CALSCALE:GREGORIAN
BEGIN:VTODO
CREATED:20101018T155431Z
UID:C98AD237-55AD-4F7D-9009-0D355D835822
SUMMARY:Simple task
DUE;TZID=America/New_York:20101021T120000
DTSTAMP:20101018T155438Z
END:VTODO
END:VCALENDAR
""".replace("\n", "\r\n"))

    def setParameters(
        self,
        enabled=True,
        interval=25,
        taskDueDistribution=NearFutureDistribution(),
    ):
        self.enabled = enabled
        self._interval = interval
        self._taskStartDistribution = taskDueDistribution

    def run(self):
        self._call = LoopingCall(self._addTask)
        self._call.clock = self._reactor
        return self._call.start(self._interval)

    def _addTask(self):
        # Don't perform any operations until the client is up and running
        if not self._client.started:
            return succeed(None)

        calendars = self._calendarsOfType(caldavxml.calendar, "VTODO")

        while calendars:
            calendar = self.random.choice(calendars)
            calendars.remove(calendar)

            # Copy the template task and fill in some of its fields
            # to make a new task to create on the calendar.
            vcalendar = self._taskTemplate.duplicate()
            vtodo = vcalendar.mainComponent()
            uid = str(uuid4())
            due = self._taskStartDistribution.sample()
            vtodo.replaceProperty(Property("CREATED", DateTime.getNowUTC()))
            vtodo.replaceProperty(Property("DTSTAMP", DateTime.getNowUTC()))
            vtodo.replaceProperty(Property("DUE", due))
            vtodo.replaceProperty(Property("UID", uid))

            href = '%s%s.ics' % (calendar.url, uid)
            d = self._client.addEvent(href, vcalendar)
            return self._newOperation("create", d)


class Resetter(BaseProfile):
    """
    A Calendar user who resets their account and re-downloads everything.
    """

    def setParameters(
        self,
        enabled=True,
        interval=600,
    ):
        self.enabled = enabled
        self._interval = interval

    def run(self):
        self._call = LoopingCall(self._resetAccount)
        self._call.clock = self._reactor
        return self._call.start(self._interval)

    def _resetAccount(self):
        # Don't perform any operations until the client is up and running
        if not self._client.started:
            return succeed(None)

        return self._client.reset()


class OperationLogger(SummarizingMixin):
    """
    Profiles will initiate operations which may span multiple requests.  Start
    and stop log messages are emitted for these operations and logged by this
    logger.
    """
    formats = {
        u"start": u"%(user)s - - - - - - - - - - - %(label)8s BEGIN %(lag)s",
        u"end": u"%(user)s - - - - - - - - - - - %(label)8s END [%(duration)5.2f s]",
        u"failed": u"%(user)s x x x x x x x x x x x %(label)8s FAILED %(reason)s",
    }

    lagFormat = u'{lag %5.2f ms}'

    # the response time thresholds to display together with failing % count threshold
    _thresholds_default = {
        "operations": {
            "limits": [0.1, 0.5, 1.0, 3.0, 5.0, 10.0, 30.0],
            "thresholds": {
                "default": [100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0],
            }
        }
    }
    _lag_cut_off = 1.0      # Maximum allowed median scheduling latency, seconds
    _fail_cut_off = 1.0     # % of total count at which failed requests will cause a failure

    _fields_init = [
        ('operation', -30, '%-30s'),
        ('count', 8, '%8s'),
        ('failed', 8, '%8s'),
    ]

    _fields_extend = [
        ('mean', 8, '%8.4f'),
        ('median', 8, '%8.4f'),
        ('stddev', 8, '%8.4f'),
        ('avglag (ms)', 12, '%12.4f'),
        ('STATUS', 8, '%8s'),
    ]

    def __init__(self, outfile=None, **params):
        self._perOperationTimes = {}
        self._perOperationLags = {}
        if outfile is None:
            outfile = sys.stdout
        self._outfile = outfile

        # Load parameters from config
        if "thresholdsPath" in params:
            with open(params["thresholdsPath"]) as f:
                jsondata = json.load(f)
        elif "thresholds" in params:
            jsondata = params["thresholds"]
        else:
            jsondata = self._thresholds_default
        self._thresholds = [[limit, {}] for limit in jsondata["operations"]["limits"]]
        for ctr, item in enumerate(self._thresholds):
            for k, v in jsondata["operations"]["thresholds"].items():
                item[1][k] = v[ctr]

        self._fields = self._fields_init[:]
        for threshold, _ignore_fail_at in self._thresholds:
            self._fields.append(('>%g sec' % (threshold,), 10, '%10s'))
        self._fields.extend(self._fields_extend)

        if "lagCutoff" in params:
            self._lag_cut_off = params["lagCutoff"]

        if "failCutoff" in params:
            self._fail_cut_off = params["failCutoff"]

        self._fail_if_no_push = params.get("failIfNoPush", False)

    def observe(self, event):
        if event.get("type") == "operation":
            event = event.copy()
            lag = event.get('lag')
            if lag is None:
                event['lag'] = ''
            else:
                event['lag'] = self.lagFormat % (lag * 1000.0,)

            self._outfile.write(
                (self.formats[event[u'phase']] % event).encode('utf-8') + '\n')

            if event[u'phase'] == u'end':
                dataset = self._perOperationTimes.setdefault(event[u'label'], [])
                dataset.append((event[u'success'], event[u'duration']))
            elif lag is not None:
                dataset = self._perOperationLags.setdefault(event[u'label'], [])
                dataset.append(lag)

    def _summarizeData(self, operation, data):
        avglag = mean(self._perOperationLags.get(operation, [0.0])) * 1000.0
        data = SummarizingMixin._summarizeData(self, operation, data)
        return data[:-1] + (avglag,) + data[-1:]

    def report(self, output):
        output.write("\n")
        self.printHeader(output, [
            (label, width)
            for (label, width, _ignore_fmt) in self._fields
        ])
        self.printData(
            output,
            [fmt for (label, width, fmt) in self._fields],
            sorted(self._perOperationTimes.items())
        )

    _LATENCY_REASON = "Median %(operation)s scheduling lag greater than %(cutoff)sms"
    _FAILED_REASON = "Greater than %(cutoff).0f%% %(operation)s failed"
    _PUSH_MISSING_REASON = "Push was configured but no pushes were received by clients"

    def failures(self):
        reasons = []

        for operation, lags in self._perOperationLags.iteritems():
            if median(lags) > self._lag_cut_off:
                reasons.append(self._LATENCY_REASON % dict(
                    operation=operation.upper(), cutoff=self._lag_cut_off * 1000))

        for operation, times in self._perOperationTimes.iteritems():
            failures = len([success for (success, _ignore_duration) in times if not success])
            if failures * 100.0 / len(times) > self._fail_cut_off:
                reasons.append(self._FAILED_REASON % dict(
                    operation=operation.upper(), cutoff=self._fail_cut_off))

        if self._fail_if_no_push and "push" not in self._perOperationTimes:
            reasons.append(self._PUSH_MISSING_REASON)

        return reasons
