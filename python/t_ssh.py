#!/usr/bin/python
# -*- coding: utf-8 -*-

"""Monitor a remote weblog over SSH
  USAGE: ssh-weblog.py user@host 
"""

from twisted.conch.ssh import transport, userauth, connection, channel
from twisted.conch.ssh.common import NS
from twisted.internet import defer, protocol, reactor
import zope.interface

# from twisted.python import log
# from getpass import getpass

import struct
import sys
import os

# import webloglib as wll

(USER, HOST, CMD) = (None, None, None)


class Transport(transport.SSHClientTransport):

    def verifyHostKey(self, hostKey, fingerprint):
        print 'host key fingerprint: %s' % fingerprint
        return defer.succeed(1)

    def connectionSecure(self):
        self.requestService(UserAuth(USER, Connection()))


class UserAuth(userauth.SSHUserAuthClient):

    def getPassword(self):

        # return defer.succeed(getpass("password: "))

        return defer.succeed('FGFDfgfd')

    def getPublicKey(self):
        return   # Empty implementation: always use password auth


class Connection(connection.SSHConnection):

    def serviceStarted(self):
        self.openChannel(Channel(2 ** 16, 2 ** 15, self))


class Channel(channel.SSHChannel):

    name = 'session'  # must use this exact string

    def openFailed(self, reason):
        print '"%s" failed: %s' % (CMD, reason)

    def channelOpen(self, data):
        self.welcome = data  # Might display/process welcome screen

        # print self.welcome
        # d = self.conn.sendRequest(self,'exec',NS(CMD),wantReply=1)
        # print "exec cmd success"

        d = self.conn.sendRequest(self, 'exec', NS('pwd'), wantReply=1)
        print '-' * 10

    def dataReceived(self, data):
        recs = data.strip().split('\n')
        for rec in recs:
            print rec,

    def closed(self):
        self.loseConnection()
        reactor.stop()


if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.stderr.write('__doc__')
        sys.exit()
    (USER, HOST) = sys.argv[1].split('@')
    CMD = 'ls /var'
    protocol.ClientCreator(reactor, Transport).connectTCP(HOST, 22)
    reactor.run()
