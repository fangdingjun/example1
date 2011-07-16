#!/usr/bin/python
# -*- coding: utf-8 -*-

"""this chinese test program"""


def test():
    a = \
        raw_input('\xc7\xeb\xca\xe4\xc8\xeb\xce\xc4\xbc\xfe\xc3\xfb\xa3\xba'
                  )

    # print "you conutry is ",a

    try:
        f = open(a)
    except:
        print '\xce\xc4\xbc\xfe\xc3\xfb\xb2\xbb\xd5\xfd\xc8\xb7'
        exit(1)

    for line in f:
        print line.strip()
    f.close()


if __name__ == '__main__':
    test()
