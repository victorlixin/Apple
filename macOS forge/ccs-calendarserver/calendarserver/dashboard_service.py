##
# Copyright (c) 2012-2017 Apple Inc. All rights reserved.
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


from twext.enterprise.jobs.jobitem import JobItem

from twisted.internet.defer import inlineCallbacks, succeed, returnValue
from twisted.internet.error import ConnectError
from twisted.internet.protocol import Factory
from twisted.protocols.basic import LineReceiver

from twistedcaldav.config import config

from txdav.common.datastore.work.load_work import TestWork
from txdav.dps.client import DirectoryService as DirectoryProxyClientService
from txdav.who.cache import CachingDirectoryService

from twext.enterprise.jobs.queue import WorkerConnectionPool

import json

"""
Protocol and other items that enable introspection of the server. This will include
server protocol analysis statistics, job queue load, and other useful information that
a server admin or developer would like to keep an eye on.
"""


class DashboardProtocol (LineReceiver):
    """
    A protocol that receives a line containing a JSON object representing a request,
    and returns a line containing a JSON object as a response.
    """

    unknown_cmd = json.dumps({"result": "unknown command"})
    bad_cmd = json.dumps({"result": "bad command"})

    def lineReceived(self, line):
        """
        Process a request which is expected to be a JSON object.

        @param line: The line which was received with the delimiter removed.
        @type line: C{bytes}
        """

        # Look for exit
        if line in ("exit", "quit"):
            self.sendLine("Done")
            self.transport.loseConnection()
            return

        def _write(result):
            self.sendLine(result)

        try:
            j = json.loads(line)
            if isinstance(j, list):
                self.process_data(j)
        except (ValueError, KeyError):
            _write(self.bad_cmd)

    @inlineCallbacks
    def process_data(self, j):
        results = {}
        for data in j:
            if hasattr(self, "data_{}".format(data)):
                result = yield getattr(self, "data_{}".format(data))()
            elif data.startswith("stats_"):
                result = yield self.data_stats()
                result = result.get(data[6:], "")
            else:
                result = ""
            results[data] = result

        self.sendLine(json.dumps(results))

    def data_stats(self):
        """
        Return the logging protocol statistics.

        @return: a string containing the JSON result.
        @rtype: L{str}
        """
        return succeed(self.factory.logger.getStats())

    def data_slots(self):
        """
        Return the logging protocol statistics.

        @return: a string containing the JSON result.
        @rtype: L{str}
        """
        states = tuple(self.factory.limiter.dispatcher.slavestates) if self.factory.limiter is not None else ()
        results = []
        for num, status in states:
            result = {"slot": num}
            result.update(status.items())
            results.append(result)
        return succeed({"slots": results, "overloaded": self.factory.limiter.overloaded if self.factory.limiter is not None else False})

    def data_jobcount(self):
        """
        Return a count of job types.

        @return: the JSON result.
        @rtype: L{int}
        """

        return succeed(JobItem.numberOfWorkTypes())

    @inlineCallbacks
    def data_jobs(self):
        """
        Return a summary of the job queue.

        @return: a string containing the JSON result.
        @rtype: L{str}
        """

        if self.factory.store:
            txn = self.factory.store.newTransaction("DashboardProtocol.data_jobs")
            records = (yield JobItem.histogram(txn))
            yield txn.commit()
        else:
            records = {}

        returnValue(records)

    def data_job_assignments(self):
        """
        Return a summary of the job assignments to workers.

        @return: a string containing the JSON result.
        @rtype: L{str}
        """

        if self.factory.store:
            pool = self.factory.store.pool
            loads = pool.workerPool.eachWorkerLoad()
            level = pool.workerPool.loadLevel()
        else:
            loads = []
            level = 0

        return succeed({"workers": loads, "level": level})

    @inlineCallbacks
    def data_test_work(self):
        """
        Return the number of TEST_WORK items in the job queue.

        @return: a string containing the JSON result.
        @rtype: L{str}
        """

        results = {}
        if self.factory.store:
            txn = self.factory.store.newTransaction()
            results["queued"] = yield TestWork.count(txn)
            results["assigned"] = yield JobItem.count(txn, where=(JobItem.assigned != None))
            results["completed"] = WorkerConnectionPool.completed.get(TestWork.workType(), 0)
            yield txn.commit()
        else:
            results["queued"] = 0
            results["assigned"] = 0
            results["completed"] = 0

        returnValue(results)

    def data_directory(self):
        """
        Return a summary of directory service calls.

        @return: the JSON result.
        @rtype: L{str}
        """
        try:
            return self.factory.directory.stats() if self.factory.directory is not None else succeed({})
        except (AttributeError, ConnectError):
            return succeed({})


class DashboardServer(Factory):

    protocol = DashboardProtocol

    def __init__(self, logObserver, limiter):
        self.logger = logObserver
        self.limiter = limiter
        self.logger.limiter = self.limiter
        self.store = None
        self.directory = None

    def makeDirectoryProxyClient(self):
        if config.DirectoryProxy.Enabled:
            self.directory = DirectoryProxyClientService(config.DirectoryRealmName)
            if config.DirectoryCaching.CachingSeconds:
                self.directory = CachingDirectoryService(
                    self.directory,
                    expireSeconds=config.DirectoryCaching.CachingSeconds,
                    lookupsBetweenPurges=config.DirectoryCaching.LookupsBetweenPurges,
                    negativeCaching=config.DirectoryCaching.NegativeCachingEnabled,
                )
