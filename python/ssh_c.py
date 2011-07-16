#!/usr/bin/env python
# -*- coding: utf-8 -*-

import paramiko
import threading
import sys
import re
import time
import os


def start_shell(h, u, p):
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(h, 22, u, p)
    s = ssh.invoke_shell()
    w = threading.Thread(target=write_chanel, args=(s, ))

    # r = threading.Thread(target=read_chanel, args=(s, ))

    w.setDaemon(True)
    w.start()

    # w.start()

    read_chanel(s)

    # w.join()

    try:
        s.close()
        ssh.close()
    except:
        pass


def read_chanel(s):
    while True:
        d = s.recv(4096)
        if not d:
            break

       # for i in ['\x1b.*?m','\x0f','\x1b\[6;1H','\x1b\[K','\x1b25;1H']:
       #    d=re.sub(str(i),"",d)

        sys.stdout.write(d)
        sys.stdout.flush()

       # time.sleep(0.1)

    try:
        s.close()
    except:
        pass


    # os.kill(os.getpid(), 15)

    # sys.exit(0)


def write_chanel(s):
    try:
        while True:
            c = sys.stdin.read(1)
            if not c:
                s.close()
                break
            a = s.send(c)
            if a == 0:
                s.close()
                break
    except:
        pass


if __name__ == '__main__':
    import sys
    if len(sys.argv) < 4:
        print 'usage:%s host user passwd' % sys.argv[0]
        sys.exit(1)

    (host, user, passwd) = sys.argv[1:4]
    start_shell(host, user, passwd)

