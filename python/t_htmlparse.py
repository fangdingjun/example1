
#!/usr/bin/env python

import sys
import urllib
import HTMLParser

class CustomParser(HTMLParser.HTMLParser):
	selected = ('table', 'h1', 'font', 'ul', 'li', 'tr', 'td', 'a')

	def reset(self):
		HTMLParser.HTMLParser.reset(self)
		self._level_stack = []
	def handle_starttag(self, tag, attrs):
		if tag in CustomParser.selected:
			self._level_stack.append(tag)
	def handle_endtag(self, tag):
		if self._level_stack \
				and tag in CustomParser.selected \
				and tag == self._level_stack[-1]:
					self._level_stack.pop()
	def handle_data(self, data):
		if "/".join(self._level_stack) in (
				'table/tr/td',
				'table/tr/td/h1/font',
				'table/tr/td/ul/li'):
			print self._level_stack, data

if len(sys.argv) > 1:
	params = urllib.urlencode({'ip': sys.argv[1], 'action': 2})
else:
	params = None

content = unicode(urllib.urlopen('http://www.ip138.com/ips8.asp',params).read(), 'GB2312')

parser = CustomParser()
parser.feed(content)
parser.close()
