#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import socket
import select
import time
import paramiko

# import termios,tty

import threading


def conn_start(host, port):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))
    except Exception, e:
        print 'connect failed:' + str(e)
        return None

    return sock


def ssh_start(sock):
    try:
        s = paramiko.Transport(sock)
        s.start_client()
    except SSHException, e:
        print 'init ssh failed:' + str(e)
        return None
    print 'start ssh success'
    return s


def ssh_auth(paramiko, user, passwd):
    paramiko.auth_password(user, passwd)
    if not paramiko.is_authenticated():
        print 'auth failed'
        return None
    session = paramiko.open_session()
    print 'auth success'
    return session


def main(host, user, passwd):
    paramiko.util.log_to_file('ssh.log')
    sock = conn_start(host, 22)
    if sock is None:
        sys.exit(1)
    p = ssh_start(sock)
    if p is None:
        sys.exit(1)

    session = ssh_auth(p, user, passwd)
    if session is None:
        sys.exit(1)

    session.get_pty()
    session.invoke_shell()

    # sys.stdout.write("Press F6 or ^Z to send EOF.\r\n\r\n")

    import re

    def writeall(s):
        while True:
            d = sys.stdin.read(1)
            if not d:
                break
            s.send(d)
        try:
            s.close()
        except:
            pass

    writer = threading.Thread(target=writeall, args=(session, ))
    writer.setDaemon(True)
    writer.start()
    while True:
        data = session.recv(4096)
        if not data:

            # sys.stdout.write('\r\n***EOF***\r\n\r\n')
            # sys.stdout.flush()

            break
        for i in ['\x1b.*?m', '\x0f', '\x1b\[6;1H', '\x1b\[K',
                  '\x1b25;1H']:
            data = re.sub(str(i), '', data)
        sys.stdout.write(data)
        sys.stdout.flush()
    try:
        session.close()
        p.close()
        sock.close()
    except:
        pass


if __name__ == '__main__':
    import sys
    if len(sys.argv) < 4:
        print 'Usage: %s host user passwd' % sys.argv[0]
        sys.exit(0)
    host = sys.argv[1]
    user = sys.argv[2]
    passwd = sys.argv[3]
    main(host, user, passwd)
