#!/usr/bin/python
# -*- coding: utf-8 -*-

from subprocess import call
import os

key_file = os.path.join(os.path.dirname(__file__), 'idfile')
key_pub = '%s.pub' % key_file
ex_file = os.path.join(os.path.dirname(__file__), 'set_ssh.exp')


def get_hostkey(host):
    call('[ -d ~/.ssh ] || mkdir -p ~/.ssh', shell=True)
    call('ssh-keyscan %s >> ~/.ssh/known_hosts' % host, shell=True)


def set_ssh(host, user, passwd):
    call("ssh-keygen -N '' -f %s" % key_file, shell=True)
    call('expect %s %s %s %s' % (ex_file, host, user, passwd, key_pub),
         shell=True)


