#!/usr/bin/python
#coding=gbk
import wx

class myframe(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self,None,-1,"my frame")
		panel=wx.Panel(self)
		wx.StaticText(panel,-1,"username",pos=(1,20))
		wx.TextCtrl(panel,-1,"",pos=(80,20))
		b=wx.Button(panel,-1,"ok",pos=(200,20))
		wx.StaticText(panel,-1,"password",pos=(1,50))
		wx.TextCtrl(panel,-1,"",pos=(80,50))
		self.Bind(wx.EVT_BUTTON,self.OnClick,b)
	
	def OnClick(self,event):
		dlg=wx.MessageDialog(self,"hello,welcome to my wxPython","Information",
				wx.OK|wx.ICON_INFORMATION)
		dlg.ShowModal()
		dlg.Destroy()

app=wx.PySimpleApp()
frame=myframe()
frame.Show()
app.MainLoop()
