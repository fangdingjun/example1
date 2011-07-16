#!python
#coding=gbk
import sys
import os
import re
import urllib
import urllib2
import StringIO
import tempfile
import gzip

def getdata(url,title,pageno,author,filename=None,apn=None):
    user_agent='Opera/9.80 (Windows NT 5.1; u; zh-cn Presto/2.2.15 version/10.10'
    datas={'rs_strTitle_aa':title,'intLogo':0,'rs_permission':1,'apn':apn,'pID':pageno}
    headers={'User-Agent':user_agent,
            'Host':'www.tianya.cn',
            'Accept':'text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1',
            'Accept-Language':'zh-CN,zh;q=0.9,en;q=0.8',
            'Accept-Charset':'iso-8859-1, utf-8, utf-16, *;q=0.1',
            'Accept-Encoding':'deflate, gzip, x-gzip, identify, *;q=0',
            'Referer':url,
            }
    #print datas
    data=urllib.urlencode(datas)
    req=urllib2.Request(url,data,headers)
    res=urllib2.urlopen(req)
    content=res.read()

    """ ungzip the content """
    gzfile=tempfile.mktemp()
    tf=open(gzfile,"wb")
    tf.write(content)
    tf.close()
    gz=gzip.open(gzfile)
    content=gz.read()
    gz.close()
    os.unlink(gzfile)

    ff=open("z:/temp/cc.html","w")
    ff.write(content)
    ff.close()

    #print content
    p=re.compile(
            r'<TD align=center.*作者.*_blank>'+author+r'</a>.*\n.*\n.*\n<DIV class=content.*\n(.*).*<br></DIV>'
            ,re.MULTILINE|re.IGNORECASE
            )

    a=re.findall(p,content)

    if filename is None:
        file=sys.stdout
    else:
        file=filename
    if a:
        f1=open(file,"w")
        for i in a:
            #print i
            f1.write(i)
        f1.close()

if __name__ == "__main__":
    #title='[连载]绝世少年修真系列之<font color=c00000><b>《万世神兵》</b></font>'
    title='[连载]【夜读社】“卜”－－<font color=f66000><b>《莫问天机》</b></font>(斑竹推荐）'
    #url='http://www.tianya.cn/techforum/content/16/633290.shtml'
    url='http://www.tianya.cn/techforum/content/16/607545.shtml'
    #author='陈静男'
    author='我性随风'
    pageno=157
    import urllib
    c=urllib.urlopen(url).read()
    apn=re.findall(r'name="apn"\s*value="(.*?)"',c)[0]
    rs="z:/temp/wanshi.html"
    getdata(url,title,pageno,author,rs,apn)
    if os.path.exists(rs):
        os.startfile(rs)
        os.unlink(rs)
    else:
        print "get content failed"

