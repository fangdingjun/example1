# -*- coding: cp936 -*-
"""2005-06-15
看到微程朋友分析基于http的QQ协议，于是准备写一个QQ程序。原以为有些包不能用了，后来灰衣人朋友的帮助下，才知道http通讯需要打开一次，关闭一次的。而不能象socket样，一直打开不关闭。
感谢微程和灰衣人朋友的帮助。关于协议大家可以看他的blog
http://spaces.msn.com/members/mprogramer/Blog/cns!1pKnbff3FpJuGZcrsAlNZmZQ!147.entry
本程序为MIT授权
如果需要转载本程序，请保留版权信息"""

import urllib,httplib,md5,time
class qq:
	def __init__(self,qq="",pwd=""):
		self.pwd=md5.new(pwd).hexdigest()
		self.headers=""
		self.qq=qq


	def getdata(self):
		self.conn= httplib.HTTPConnection("tqq.tencent.com:8000")#这里是tqq.tencent.com的ip地址，也可以直接用域名
		self.conn.request("POST","", self.headers)
		response = self.conn.getresponse()                                      
		print response.read().decode('utf-8').encode("cp936")
		self.conn.close

	def Login(self):#登陆
		self.headers=("VER=1.0&CMD=Login&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&PS="+\
				self.pwd+\
				"&M5=1&LC=9326B87B234E7235")
		self.getdata()      


	def Query_Stat(self):#在线好友
		self.headers=("VER=1.0&CMD=Query_Stat&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&TN=50&UN=0")

		self.getdata()

	def List(self):#好友列表
		self.headers=("VER=1.0&CMD=List&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&TN=160&UN=0")

		self.getdata()

	def GetInfo(self,friend=""):#指定QQ号码的详细内容
		self.headers=("VER=1.0&CMD=GetInfo&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&LV=2&UN="+\
				friend)

		self.getdata()

	def AddToList(self,friend=""):#增加指定QQ号码为好友
		self.headers=("VER=1.0&CMD=AddToList&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&UN="+\
				friend)

		self.getdata()

	def GetMsg(self):#获取消息
		self.headers=("VER=1.0&CMD=GetMsgEx&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq)

		self.getdata()

	def SendMsg(self,friend="",msg=""):#发送消息
		self.headers=("VER=1.0&CMD=CLTMSG&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&UN="+\
				friend+"&MG="+\
				msg.decode("cp936").encode('utf-8'))

		self.getdata()

	def Logout(self):#退出登陆
		self.headers=("VER=1.0&CMD=Logout&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq)

		self.getdata()

test=qq('358736855','zhuzhu5201314')
test.Login()
test.Query_Stat()
test.List()
#test.GetInfo('他人QQ号码')
#test.AddToList('他人QQ号码')
test.GetMsg()
i=0
while i<1000:
	print i
	time.sleep(0.9)
	test.SendMsg('他人QQ号码',"一共有1000条消息，这是第"+str(i)+"条消息")
	i = i+1
test.Logout()

