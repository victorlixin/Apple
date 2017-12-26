##
# Copyright (c) 2013-2017 Apple Inc. All rights reserved.
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
##

"""
Common directory service interfaces for calendaring
"""

from txdav.common.idirectoryservice import IStoreDirectoryService, \
    IStoreDirectoryRecord
from zope.interface.interface import Attribute


__all__ = [
    "ICalendarStoreDirectoryService",
    "ICalendarStoreDirectoryRecord",
]


class ICalendarStoreDirectoryService(IStoreDirectoryService):
    """
    Directory Service for looking up users.
    """

    def recordWithCalendarUserAddress(cuaddr):  # @NoSelf
        """
        Return the record for the specified calendar user address.

        @return: Deferred resulting in the record.
        @rtype: L{Deferred} resulting in L{ICalendarStoreDirectoryRecord}
        """


class ICalendarStoreDirectoryRecord(IStoreDirectoryRecord):
    """
    Record object for calendar users.

    A record identifies a "user" in the system.
    """

    calendarUserAddresses = Attribute("Calendar users address for entity associated with the record: C{frozenset}")

    def canonicalCalendarUserAddress():  # @NoSelf
        """
        The canonical calendar user address to use for this record.

        @return: the canonical calendar user address.
        @rtype: C{str}
        """

    def calendarsEnabled():  # @NoSelf
        """
        Indicates whether the record enabled for using the calendar service.

        @return: C{True} if enabled for this service.
        @rtype: C{bool}
        """

    def enabledAsOrganizer():  # @NoSelf
        """
        Indicates that the record is allowed to be the Organizer in calendar data.

        @return: C{True} if allowed to be the Organizer.
        @rtype: C{bool}
        """

    def getCUType():  # @NoSelf
        """
        Indicates the calendar user type for this record. It is the RFC 5545 CUTYPE value.

        @return: the calendar user type.
        @rtype: C{str}
        """

    def canAutoSchedule(organizer):  # @NoSelf
        """
        Indicates that calendar data for this record can be automatically scheduled.

        @param organizer: the organizer of the scheduling message being processed
        @type organizer: C{str}

        @return: C{True} if automatically scheduled.
        @rtype: C{bool}
        """

    def getAutoScheduleMode(organizer):  # @NoSelf
        """
        Indicates the mode of automatic scheduling used for this record.

        @param organizer: the organizer of the scheduling message being processed
        @type organizer: C{str}

        @return: C{True} if automatically scheduled.
        @rtype: C{bool}
        """

    def setAutoScheduleMode(autoScheduleMode):  # @NoSelf
        """
        Sets the mode of automatic scheduling used for this record.

        @param autoScheduleMode: the new mode
        @type autoScheduleMode: L{AutoScheduleMode}
        """

    def isProxyFor(other):  # @NoSelf
        """
        Test whether the record is a calendar user proxy for the specified record.

        @param other: record to test
        @type other: L{IDirectoryRecord}

        @return: C{True} if it is a proxy.
        @rtype: C{bool}
        """

    def proxyMode(other):  # @NoSelf
        """
        Determine the proxy mode this record has in relation to the one specified.

        @param other: record for the possible user proxying to this record
        @type other: L{CalendarDirectoryRecordMixin}
        """

    def proxyFor(readWrite, ignoreDisabled=True):  # @NoSelf
        """
        Returns the set of records currently delegating to this record
        with the access indicated by the readWrite argument.  If readWrite is
        True, then write-access delegators are returned, otherwise the read-
        only-access delegators are returned.

        @param readWrite: Whether to look up read-write delegators, or
            read-only delegators
        @type readWrite: L{bool}
        @param ignoreDisabled: If L{True} disabled delegators are not returned
        @type ignoreDisabled: L{bool}

        @return: A Deferred firing with a set of records
        """