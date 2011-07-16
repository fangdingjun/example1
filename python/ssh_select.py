#!/usr/bin/env python
# -*- coding: utf-8 -*-

import paramiko
import sys
import os
from select import select


def start_shell(h, u, p):
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(h, 22, u, p)
    s = ssh.invoke_shell()
    input = sys.stdin.fileno()
    remote = s.fileno()
    p = ''

    while True:
        (r, w, e) = select([input, remote], [], [], 1)
        if input in r:
            cmd = sys.stdin.readline()
            if not cmd:
                break
            s.send(cmd)
        elif remote in r:
            o = s.recv(4096)
            if not o:
                break
            sys.stdout.write(o)
            sys.stdout.flush()

    s.close()
    ssh.close()


if __name__ == '__main__':
    import sys
    if len(sys.argv) < 4:
        print 'usage:%s host user passwd' % sys.argv[0]
        sys.exit(1)

    (host, user, passwd) = sys.argv[1:4]
    start_shell(host, user, passwd)

