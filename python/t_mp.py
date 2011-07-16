#!/usr/bin/env python
# -*- coding: utf-8 -*-

import multiprocessing as mp
import random
import time
import sys


def worker(q, output):
    while True:
        item = q.get()
        if str(item) == 'STOP':
            msg = '%s got stop signal,stop ...' \
                % mp.current_process().name
            output.put(msg)
            break
        do_worker(item, output)


def do_worker(item, output):
    msg = '%s got %s' % (mp.current_process().name, item)
    output.put(msg)
    time.sleep(random.random() * 4)


def test():
    print 'cpu number: %d' % mp.cpu_count()
    q = mp.Queue()

    # m=mp.Manager()

    errors = mp.Queue()

    # task_done.qsize=100

    num_workers = 4
    workers = []
    for i in range(num_workers):
        w = mp.Process(target=worker, args=(q, errors))
        w.start()
        workers.append(w)

    for i in range(20):
        q.put('aaa%d' % i)

    for i in range(num_workers):
        q.put('STOP')
    for w in workers:
        w.join()
    while True:
        try:
            info = errors.get_nowait()
            print info
        except:

            # print sys.exc_info()

            break


if __name__ == '__main__':
    test()
