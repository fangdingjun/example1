#!/usr/bin/python
#coding=gbk   
import httplib   
conn = httplib.HTTPConnection("www.tianya.cn", 80, False)   
conn.request('GET', '/techforum/content/16/645264.shtml', headers = {"Host": "www.google.cn",   
	"User-Agent": "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.1) Gecko/20090624 Firefox/3.5",   
	"Accept": "text/plain",
	"Referer": "http://www.tianya.cn"
	}
	)   
res = conn.getresponse()   
#print 'version:', res.version   
#print 'reason:', res.reason   
#print 'status:', res.status   
#print 'msg:', res.msg   
#print 'headers:'
#print "\t".join(["%s: %s\n" % (k,v) for k,v in res.getheaders()])
#html   
#print '\n' + '-' * 50 + '\n'   
#print res.read()   
content=res.read()
print content
conn.close()  

