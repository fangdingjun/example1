# -*- coding: cp936 -*-
"""2005-06-15
����΢�����ѷ�������http��QQЭ�飬����׼��дһ��QQ����ԭ��Ϊ��Щ���������ˣ��������������ѵİ����£���֪��httpͨѶ��Ҫ��һ�Σ��ر�һ�εġ���������socket����һֱ�򿪲��رա�
��л΢�̺ͻ��������ѵİ���������Э���ҿ��Կ�����blog
http://spaces.msn.com/members/mprogramer/Blog/cns!1pKnbff3FpJuGZcrsAlNZmZQ!147.entry
������ΪMIT��Ȩ
�����Ҫת�ر������뱣����Ȩ��Ϣ"""

import urllib,httplib,md5,time
class qq:
	def __init__(self,qq="",pwd=""):
		self.pwd=md5.new(pwd).hexdigest()
		self.headers=""
		self.qq=qq


	def getdata(self):
		self.conn= httplib.HTTPConnection("tqq.tencent.com:8000")#������tqq.tencent.com��ip��ַ��Ҳ����ֱ��������
		self.conn.request("POST","", self.headers)
		response = self.conn.getresponse()                                      
		print response.read().decode('utf-8').encode("cp936")
		self.conn.close

	def Login(self):#��½
		self.headers=("VER=1.0&CMD=Login&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&PS="+\
				self.pwd+\
				"&M5=1&LC=9326B87B234E7235")
		self.getdata()      


	def Query_Stat(self):#���ߺ���
		self.headers=("VER=1.0&CMD=Query_Stat&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&TN=50&UN=0")

		self.getdata()

	def List(self):#�����б�
		self.headers=("VER=1.0&CMD=List&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&TN=160&UN=0")

		self.getdata()

	def GetInfo(self,friend=""):#ָ��QQ�������ϸ����
		self.headers=("VER=1.0&CMD=GetInfo&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&LV=2&UN="+\
				friend)

		self.getdata()

	def AddToList(self,friend=""):#����ָ��QQ����Ϊ����
		self.headers=("VER=1.0&CMD=AddToList&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&UN="+\
				friend)

		self.getdata()

	def GetMsg(self):#��ȡ��Ϣ
		self.headers=("VER=1.0&CMD=GetMsgEx&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq)

		self.getdata()

	def SendMsg(self,friend="",msg=""):#������Ϣ
		self.headers=("VER=1.0&CMD=CLTMSG&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq+"&UN="+\
				friend+"&MG="+\
				msg.decode("cp936").encode('utf-8'))

		self.getdata()

	def Logout(self):#�˳���½
		self.headers=("VER=1.0&CMD=Logout&SEQ="+\
				str(int(time.time()*100)%(10**5))+"&UIN="+\
				self.qq)

		self.getdata()

test=qq('358736855','zhuzhu5201314')
test.Login()
test.Query_Stat()
test.List()
#test.GetInfo('����QQ����')
#test.AddToList('����QQ����')
test.GetMsg()
i=0
while i<1000:
	print i
	time.sleep(0.9)
	test.SendMsg('����QQ����',"һ����1000����Ϣ�����ǵ�"+str(i)+"����Ϣ")
	i = i+1
test.Logout()

