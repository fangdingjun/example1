#!/usr/bin/python
# -*- coding: utf-8 -*-

import logging
import time
import os
from subprocess import call

class CalledProcessError(Exception):
    def __init__(self,retcode,cmd):
        self.cmd=cmd
        self.retcode=retcode
    def __str__(self):
        return "Command '%s' returned non-zero exit status %d" % (self.cmd,self.retcode)
    def __repr__(self):
        return self.__str__()

def initlog(filename):
    mylog=logging.getLogger(__name__)
    h=logging.FileHandler(filename)
    f=logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")
    h.setFormatter(f)
    mylog.addhandler(h)
    mylog.setLevel(logging.DEBUG)
    return mylog

def check_call(*args,**kargs):
    cmd=kargs.get("args")
    if not cmd:
        cmd=args[0]
    retcode=call(*args,**kargs)
    if retcode:
        raise CalledProcessError(retcode,cmd)

log_file=os.path.join(os.path.dirname(__file__),"info_%s.log")
t=strftime("%Y%m%d%H%M",time.localtime())
log=initlog(log_file % t)

if __name__ == "__main__":
    check_call("ping -n 1 10.10.10.10",shell=True)
    #subprocess.check_call("ping -n 1 10.10.10.10",shell=True)
