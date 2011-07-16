#!/usr/bin/env python
# -*- coding: utf-8 -*-
from win32inetcon import *
import sys
from ctypes import *
from socket import *
import threading
import re
import win32api
import traceback

inet = windll.LoadLibrary('wininet.dll')

InternetOpen = inet.InternetOpenA
InternetOpen.restype = c_void_p
InternetOpen.argtypes = [c_char_p, c_int, c_char_p, c_char_p, c_int]

InternetOpenUrl = inet.InternetOpenUrlA
InternetOpenUrl.restype = c_void_p
InternetOpenUrl.argtypes = [
    c_void_p,
    c_char_p,
    c_char_p,
    c_int,
    c_int,
    c_void_p,
    ]

HttpQueryInfoA = inet.HttpQueryInfoA
HttpQueryInfoA.restype = c_int
HttpQueryInfoA.argtypes = [c_void_p, c_int, c_void_p, c_void_p,
                           c_void_p]

InternetCloseHandle = inet.InternetCloseHandle
InternetCloseHandle.restype = c_int
InternetCloseHandle.argtypes = [c_void_p]

InternetReadFile = inet.InternetReadFile
InternetReadFile.restype = c_int
InternetReadFile.argtypes = [c_void_p, c_void_p, c_int, c_void_p]

# debug = False


def proxy(sock):
    buffer = ''
    buf1 = []
    sock.settimeout(5 * 60)
    while True:
        try:
            data = sock.recv(4096)
        except:

            # traceback.print_exc()

            sys.stdout.write('recv:',
                             win32api.FormatMessage(win32api.GetLastError()))
            break
        if not data:
            break
        buf1.append(data)
        if '\r\n\r\n' in data:
            buffer = ''.join(buf1)
            buf1 = []
            url = re.findall("[GET|POST]\s+([^\s]+)\s+HTTP", buffer)[0]
            h = buffer.split('\r\n')[1:]
            ua = ''

            # print h

            for h1 in h:
                if 'accept-encoding:' in h1.lower():

                    # print " removeing",h1

                    h.remove(h1)

                # if "connect:" in h[i].lower():
                #    h.remove(h1)
                #    h[i]="Connection: Keep-alive"

                if 'user-agent:' in h1.lower():
                    ua = h1.split(':')[1].strip()

                    # print "ua",ua

            headers = '\r\n'.join(h)
            if not ua:
                ua = 'myapp/0.1'

            # sys.stdout.write("headers from client:\n%s" % headers)

            buffer = ''
            try:
                if url:
                    print 'GET %s' % repr(url)
                    hi = InternetOpen(c_char_p(ua),
                            INTERNET_OPEN_TYPE_PRECONFIG, None, None, 0)
                    if not hi:
                        print 'InternetOpen failed,error: %s' \
                            % win32api.FormatMessage(win32api.GetLastError())
                    hdl = InternetOpenUrl(
                        hi,
                        c_char_p(url),
                        c_char_p(headers),
                        c_int(-1),
                        INTERNET_FLAG_EXISTING_CONNECT
                            | INTERNET_FLAG_KEEP_CONNECTION,
                        None,
                        )
                    if not hdl:
                        print 'InternetOpenUrl failed, error: %s' \
                            % win32api.FormatMessage(win32api.GetLastError())
                        break

                    hdr = create_string_buffer(4096)
                    buflen = c_int(-1)
                    r = HttpQueryInfoA(hdl,
                            HTTP_QUERY_RAW_HEADERS_CRLF, byref(hdr),
                            byref(buflen), None)
                    if r:

                        # print "headers from server: %s"  % repr(hdr.value)

                        sys.stdout.write('headers from server:\n%s'
                                % hdr.value)
                        sock.send(hdr.value)  # send header to client
                    else:
                        print 'HttpQueryInfo failed,error: %s' \
                            % win32api.FormatMessage(win32api.GetLastError())
                        break
                    buf = create_string_buffer(4096)
                    l = c_int()
                    while True:
                        r = InternetReadFile(hdl, byref(buf), 4096,
                                byref(l))
                        if not r:
                            print '2:internetreadfile failed, error code: %s' \
                                % win32api.FormatMessage(win32api.GetLastError())
                            break
                        if l.value > 0:
                            try:
                                sock.send(buf.value)
                                sys.stdout.write(buf.value)
                            except:

                                # traceback.print_exc()

                                print win32api.FormatMessage(win32api.GetLastError())
                                break
                        else:

                            # print repr(buf.value)

                            break
                    InternetCloseHandle(hdl)
                    InternetCloseHandle(hi)
                    break
            except:
                traceback.print_exc()
                break

    # print "close socket"

    sock.close()


    # InternetCloseHandle(hdl)
    # InternetCloseHandle(hi)


def server(host, port):
    main_sock = socket(AF_INET, SOCK_STREAM)
    main_sock.bind((host, port))
    main_sock.listen(5)
    while True:
        (new_sock, addr) = main_sock.accept()
        t = threading.Thread(target=proxy, args=(new_sock, ))
        t.setDaemon(True)
        t.start()


if __name__ == '__main__':
    (HOST, PORT) = ('0.0.0.0', 8010)
    print 'start proxy server at %s:%s ...' % (HOST, PORT)
    try:
        server(HOST, PORT)
    except:
        traceback.print_exc()
        print 'server exiting ..'
        sys.exit(0)

