#!python
# coding=gbk
import sys
from HTMLParser import HTMLParser

class MyHTMLParser(HTMLParser):
	def __init__(self):
		HTMLParser.__init__(self)
		self.links = []
		self.datas = []
		self.tags = []
		self.start=0
		self.d={}
		self._stack=[]
		self.isauth=0
		self.isauthcontent=0
	
	#def handle_startendtag(self,tag,attrs):
	#	pass
	#def handle_charref(self,name):
	#	pass
	#def handle_
	def handle_starttag(self, tag, attrs):
		#print "Encountered the beginning of a '%s' tag" % tag
		#if len(attrs) == 0:pass
		#else:
		#	self.tags.append(tag)
		if tag == 'title':
			print "start parse"
			self.start=1
		if self.start == 1:
			if tag == 'table':
				if len(self._stack) == 0:
					print "push table"
					self._stack.append(tag)
				else:
					self._stack=[]
			if tag == 'tr':
				if len(self._stack) == 1:
					print "push tr"
					self._stack.append(tag)
				else:
					self._stack=[]
			if tag == 'td':
				if len(self._stack) == 2 or len(self._stack) == 3:
					print "push td"
					self._stack.append(tag)
				else:
					self._stack=[]
			if tag == 'font':
				if len(self._stack) == 4:
					print "push font"
					self._stack.append(tag)
				else:
					self._stack=[]
			if tag == 'a':
				if len(self._stack) == 5:
					print "push a"
					self._stack.append(tag)
				else:
					self._stack=[]
			if tag == 'div' and self.isauth == 1:
				for k,v in attrs:
					if k == "class" and v == "content":
						self.isauthcontent=1
						return
					else:
						self.isauthcontent=0
			

	def handle_endtag(self,tag):
		#print "End the '%s' tag" % tag
		pass
	def handle_data(self,data):
		#print "begin to parse data"
		#d=data.strip()
		#if d != '':
			#self.datas.append(d)
			#print d
		#print self._stack;
		if len(self._stack) == 6:
			#if data.strip() == 'amy20080710':
			#	self.isauth = 1
			#else:
			#	self.isauth=0
			print data
		if self.isauthcontent == 1:
			print data

if __name__ == "__main__":
	f=open("c:/tmp/e.txt")
	html_code=f.read()
	#print html_code
	#html_code=unicode(html_code,'GB2312')
	f.close()
	hp = MyHTMLParser()
	hp.feed(html_code)
	hp.close()
	#print(hp.tags)
	#for d in hp.datas:
		#print d.strip()
	#print(hp.datas)
