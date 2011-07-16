#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
version: 0.1
author:fandingjun
"""

import logging
import sys


class InitLog(object):

    """
    set log to file or stderr
    set log formater
    set log level
    function
        loglevel(level)
            set log level
    """

    def __init__(
        self,
        filename=None,
        logname=None,
        level='info',
        ):

        if logname is None:
            logname = 'test_log'
        self.log = logging.getLogger(logname)
        self.loglevel(level)
        if filename:
            try:
                file_pointer = open(filename, 'a')
            except IOError:
                file_pointer = sys.stderr
        else:
            file_pointer = sys.stderr

        handler = logging.StreamHandler(file_pointer)
        formatter = \
            logging.Formatter('%(asctime)s - %(levelname)s - %(message)s'
                              , '%Y-%m-%d %H:%M:%S')
        handler.setFormatter(formatter)
        self.log.addHandler(handler)

    def loglevel(self, level):
        """
        set log level
        """

        if level.upper() == 'INFO':
            level = logging.INFO
        elif level.upper() == 'DEBUG':
            level = logging.DEBUG
        elif level.upper() == 'ERROR':
            level = logging.ERROR
        elif level.upper() == 'CRITICAL':
            level = logging.CRITICAL
        else:
            level = logging.INFO
        self.log.setLevel(level)


def test(log_handler):
    """
    this is a test
    """

    print log_handler
    log_handler.debug('this is a log test')
    log_handler.info('info log')
    log_handler.warn('warn log')
    log_handler.error('error log')


if __name__ == '__main__':
    test(InitLog(level='info').log)
