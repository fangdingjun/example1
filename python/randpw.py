#!/usr/bin/python
"""
this module can gerate some random characters
"""
import sys
import random
import string

def usage():
    """this script generate random password use letters digits and special character"""
    print "Usage:./randpw.py num"
    exit(1)

def randpw(num):
    """generate random characters\nUsage: randpw(num)\n\tnum between 1-1024"""
    pw=''
    seed=string.letters + string.digits + string.punctuation
    #print seed
    for i in xrange(num):
        pw += seed[random.randrange(1,len(seed))]
    return pw

def main():
    if len(sys.argv) == 2:
        try:
            num = int(sys.argv[1])
        except:
            usage()
        if num in xrange(1,1024):
            print randpw(num)
        else:
            usage()
    else:
         print randpw(8)

if __name__ == "__main__":
    main()
