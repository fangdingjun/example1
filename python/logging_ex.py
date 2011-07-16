#!/usr/bin/python
# -*- coding: utf-8 -*-

import logging
import sys
import os
def log_test():
    l1=logging.getLogger('%s' % os.path.basename(sys.argv[0]))
    o=logging.StreamHandler()
    f=logging.Formatter("%(asctime)s - %(filename)s:%(funcName)s():%(lineno)d - %(process)d - %(levelname)s - %(message)s","%Y-%m-%d %H:%M:%S")
    o.setFormatter(f)
    l1.addHandler(o)
    l1.setLevel(logging.DEBUG)
    l1.debug("debug message")
    l1.info("this is info log")
    l1.warning("this is warnging")
    l1.error("/tmp/a.txt:no such file")

if __name__ == "__main__":
    log_test()
