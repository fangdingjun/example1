#!/usr/bin/env python
# -*- coding: utf-8 -*-
from select import select
import sys

def test():
    input = sys.stdin.fileno()
    while 1:
        (r, w, e) = select([input], [], [], 1)
        if input in r:
            s = sys.stdin.readline()
            if not s:
                break
            print s.strip()


if __name__ == '__main__':
    test()

