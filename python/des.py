#!/usr/bin/python
# -*- coding: utf-8 -*-

import binascii
from Crypto.Cipher import DES

default_sharekey = '1B92FB65AE3C015F'


def encrypt(text, sharekey=default_sharekey):
    obj = DES.new(binascii.a2b_hex(sharekey), DES.MODE_CBC)
    p_txt = text
    padding_len = 8 - len(p_txt) % 8
    if padding_len != 8:

        # tmp_txt = p_txt + chr(padding_len)*(padding_len)
        # p_txt = tmp_txt

        p_txt = p_txt + chr(padding_len) * padding_len

    ciph_txt = obj.encrypt(p_txt)
    return ciph_txt


def decrypt(ciph, sharekey=default_sharekey):
    obj = DES.new(binascii.a2b_hex(sharekey), DES.MODE_CBC)

    # return obj.decrypt(ciph).strip('\x01').strip('\x02').strip('\x03').strip('\x04').strip('\x05').strip('\x06').strip('\x07')

    o = obj.decrypt(ciph)
    for i in range(1, 8):
        o = o.strip(chr(i))
    return o


if __name__ == '__main__':
    test_text = 'This ia a test!'
    ciph = encrypt(test_text)
    origin_text = decrypt(ciph)
    print origin_text

