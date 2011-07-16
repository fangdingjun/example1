#!/usr/bin/python
# -*- coding: utf-8 -*-

# optimize code

try:
    import psyco
    psyco.full()
except:
    pass
from pyquery import PyQuery as pq
import urllib
import urllib2
import time
import logging


def get_author_content(content, author):
    """get the content of author
    content: the  html of all content
    author: the author
    return is author's content
    """

    c = ''
    doc = pq(content)
    tables = doc.find('#pContentDiv table')

    # print author

    for i in range(len(tables)):
        t = tables.eq(i).find('tr td a').text()

        # print t

        if t == author:
            c1 = tables.eq(i).next().html()

            # print "=" * 10

            if 'table' in c1 or 'div' in c1:
                d = pq(c1)
                d.remove('table')
                d.remove('div')
                c1 = d.html()
            c = c + c1

            # c=c+"\n"

    return c


def get_attr(content):
    """return value is a dic below:
    rs_strTitle_aa:xxxx
    intLogo:0
    rs_permission:1
    apn:10xxxx
    pID:1
    idItem:12
    strItem:
    chrAuthor:
    idArticle:
    strTitle:
    idSign:1
    ttitem:16
    pageAll:1
    Submit:Response
    Create:+
    PicDesc:None
    strAlbumPicURL:http://
    submit2:
    """

    d = pq(content)
    attr = {}
    input = d.find('input')
    for i in xrange(len(input)):
        name = input.eq(i).attr('name')
        value = input.eq(i).attr('value')
        attr[name] = value
    return attr


def get_url(url, pageno=1, arg={}):
    """get content by url,pageno
    url: the url of page
    pangeno: the num of page
    arg: title,apn...
    return is utf-8 content
    """

    user_agent = 'Opera/9.80 (Windows NT 5.1; zh-cn version/10.10)'
    try:
        datas = {
            'rs_strTitle_aa': arg['rs_strTitle_aa'].encode('utf-8'),
            'intLogo': arg['intLogo'],
            'rs_permission': arg['rs_permission'],
            'apn': arg['apn'],
            'pID': pageno,
            }
        headers = {
            'UserAgent': user_agent,
            'Host': 'www.tianya.cn',
            'Accept': 'text/html, application/xml; q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1',
            'Accept-Language': 'zh-CN,zh;q=0.9,en;q=0.8',
            'Accept-Charset': 'iso-8859-1, utf-8, utf-16, *;q=0.1',
            'Referer': url,
            }
    except:
        headers = {}
        datas = {}
        data = None
    if headers.has_key('Host') and datas.has_key('pID'):
        data = urllib.urlencode(datas)
    else:
        data = None

    req = urllib2.Request(url, data, headers)
    content = urllib2.urlopen(req).read()
    try:

        # content=content.decode("gbk",'ignore').encode("utf-8",'ignore')

        content = content.decode('gbk', 'ignore')
    except:
        print 'decode gbk error'

    # print "=" * 20

    return content


def start(url, target, debug=0):

    # begin to set log

    log = logging.getLogger('getauthor')
    if debug:
        log.setLevel(logging.DEBUG)
    else:
        log.setLevel(logging.INFO)
    f = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s',
                          '%Y-%m-%d %H:%M:%S')
    h = logging.StreamHandler()
    h.setFormatter(f)
    log.addHandler(h)

    # end to set log

    log.info('begin to process %s' % url)
    attr = get_attr(get_url(url))
    page_all = int(attr['pageAll'])
    log.debug('title %s' % attr['strTitle'].encode('gbk'))
    log.debug('author %s' % attr['chrAuthor'].encode('gbk'))
    log.debug('total %d pages.' % page_all)
    author = attr['chrAuthor']

    # saveto="z:/tianshi.html"

    f = open(target, 'wb')
    for i in xrange(1, page_all + 1):
        log.debug('get page %d ...' % i)
        c = get_author_content(get_url(url, i, attr), author)
        f.write(c.encode('utf-8'))
        log.debug('get page %d done.' % i)
        time.sleep(0.3)
    f.close()
    log.info('process page done.')


if __name__ == '__main__':

    # url="http://www.tianya.cn/techforum/content/16/590138.shtml"

    url = 'http://www.tianya.cn/techforum/content/16/628184.shtml'
    saveto = 'z:/qianyu.html'
    start(url, saveto, 1)
