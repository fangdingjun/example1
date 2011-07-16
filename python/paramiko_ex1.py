#!/usr/bin/python
# -*- coding: utf-8 -*-

import paramiko
import sys
if len(sys.argv) < 4:
    print 'usage: %s host user passwd' % sys.argv[0]
    sys.exit(1)

host = sys.argv[1]
user = sys.argv[2]
pw = sys.argv[3]
ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect(host, 22, user, pw)
cmd = ['ls', 'pwd', 'who']
for c in cmd:
    (i, o, e) = ssh.exec_command(c)
    for l in o:
        print l.strip()
ssh.close()
