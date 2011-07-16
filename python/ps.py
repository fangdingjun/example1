#!/usr/bin/env python
# -*- coding: utf-8 -*-

import psutil
procs = psutil.get_process_list()
print '%-13s %-5s %-5s %-5s %-5s %-s' % (
    'USERNAME',
    'PID',
    'PPID',
    'CPU%',
    'MEM%',
    'CMD',
    )
for p in procs:
    cmd = ''
    for c in p.cmdline:
        cmd = cmd + ' ' + c
    user = p.username.split('\\')[1]
    pid = p.pid
    ppid = p.ppid
    if ppid is None:
        ppid = 0
    cpu = p.get_cpu_percent()
    mem = p.get_memory_percent()
    print """%-13s %-5d %-5d %-3.2f %-3.2f %-s""" % (
        user,
        pid,
        ppid,
        cpu,
        mem,
        cmd,
        )

