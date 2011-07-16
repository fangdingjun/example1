#!/usr/bin/python
# -*- coding: utf-8 -*-

"""my exercise for wxpython"""

import wx
import os
import win32api
import sys

fn = os.path.join(os.path.dirname(sys.argv[0]), 'error.log')
fp = open(fn, 'w', 0)

sys.modules['sys'].stdout = fp
sys.modules['sys'].stderr = fp

# print sys.argv
# print sys.path


class WordExcelError(Exception):

    pass


class myframe(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, parent=None, id=-1, title='wanghaiying'
                          , size=(300, 170))
        exeName = \
            win32api.GetModuleFileName(win32api.GetModuleHandle(None))

        # icon=wx.Icon('bnb.ico',wx.BITMAP_TYPE_ANY)

        icon = wx.Icon(exeName, wx.BITMAP_TYPE_ICO)
        self.SetIcon(icon)
        mainsizer = wx.BoxSizer(wx.VERTICAL)
        panel = wx.Panel(self, -1)

        # sizer=wx.FlexGridSizer(rows=2,cols=2,hgap=20,vgap=0)

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add((20, 10))
        sizer.Add(wx.StaticText(panel, -1, '1.select excel file'), 0,
                  wx.ALIGN_CENTER)

        # sizer.Add(wx.StaticText(panel,-1," "),0,0)

        mainsizer.Add(sizer, 0)

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add((20, -1))
        t_e = wx.TextCtrl(panel, -1, '', size=(200, 20))
        sizer.Add(t_e, 0, 0)
        sizer.Add((10, -1))
        b1 = wx.Button(panel, -1, label='...', size=(30, 20))
        sizer.Add(b1, 0, 0)
        self.Bind(wx.EVT_BUTTON, self.OnClick, b1)
        self.p_e = t_e
        mainsizer.Add(sizer)
        mainsizer.Add((-1, 10))
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add((20, -1))
        sizer.Add(wx.StaticText(panel, -1, '2.select word file'), 0, 0)
        mainsizer.Add(sizer)

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add((20, -1))

        # sizer.Add(wx.StaticText(panel,-1," "),0,0)

        t_w = wx.TextCtrl(panel, -1, '', size=(200, 20))
        sizer.Add(t_w, 0, 0)
        sizer.Add((10, -1))

        # sizer=wx.BoxSizer(wx.HORIZONTAL)

        b2 = wx.Button(panel, -1, label='...', size=(30, 20))
        sizer.Add(b2, 0, 0)

        self.Bind(wx.EVT_BUTTON, self.OnClick2, b2)
        self.p_w = t_w
        mainsizer.Add(sizer)
        mainsizer.Add((-1, 10))
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add((60, -1))
        b_s = wx.Button(panel, -1, label='start', size=(40, 20))
        sizer.Add(b_s, 0, 0)
        sizer.Add((40, -1))
        b_c = wx.Button(panel, -1, label='exit', size=(40, 20))
        sizer.Add(b_c, 0, 0)
        self.Bind(wx.EVT_BUTTON, self.OnStart, b_s)
        self.Bind(wx.EVT_BUTTON, self.OnClose, b_c)

        menubar = wx.MenuBar()
        menu1 = wx.Menu()
        menu1.Append(-1, '&New')
        menu1.Append(-1, '&Open')
        menu1.Append(-1, '&Save')
        menu1.AppendSeparator()
        exit = menu1.Append(-1, '&Quit\tCtrl+Q')
        menubar.Append(menu1, '&File')
        menu2 = wx.Menu()
        menu2.Append(-1, '&Undo')
        menu2.Append(-1, '&Cut')
        menu2.Append(-1, 'C&opy')
        menu2.Append(-1, '&Paste')
        menubar.Append(menu2, '&Edit')
        self.SetMenuBar(menubar)
        self.Bind(wx.EVT_MENU, self.OnClose, exit)
        mainsizer.Add(sizer)
        panel.SetSizer(mainsizer)
        mainsizer.Fit(panel)
        panel.Fit()

    def OnClick(self, event):
        dlg = wx.FileDialog(
            self,
            message='select a file',
            defaultDir=os.getcwd(),
            defaultFile='',
            wildcard='Word files(*.xls)|*.xls',
            style=wx.OPEN | wx.CHANGE_DIR,
            )
        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPaths()

            # print "path is ",path

            self.p_e.Clear()
            self.p_e.WriteText(os.getcwd().join(path))

            # print "CWD is ",os.getcwd()

        dlg.Destroy()

    def OnClick2(self, event):
        dlg = wx.FileDialog(
            self,
            message='select a file',
            defaultDir=os.getcwd(),
            defaultFile='',
            wildcard='Word files(*.doc)|*.doc',
            style=wx.OPEN | wx.CHANGE_DIR,
            )
        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPaths()

            # print "path is ",path

            self.p_w.Clear()
            self.p_w.WriteText(os.getcwd().join(path))

            # print "CWD is ",os.getcwd()

        dlg.Destroy()

    def OnClose(self, event):
        self.Close(True)

    def OnStart(self, event):
        e = self.p_e.GetValue()
        w = self.p_w.GetValue()
        if e and w:
            msg = ''
        else:
            msg = 'please select a word or excel file'
        if msg:
            dlg = wx.MessageDialog(self, msg, 'error', wx.OK
                                   | wx.ICON_ERROR)
            dlg.ShowModal()
            dlg.Destroy()
            return

        self.process(e, w)

        msg = 'process %s and %s success' % (e, w)
        dlg = wx.MessageDialog(self, msg, 'info', wx.OK
                               | wx.ICON_INFORMATION)
        dlg.ShowModal()
        dlg.Destroy()

    def process(self, excel, word):
        import win32com.client
        e = win32com.client.Dispatch('Excel.Application')
        w = win32com.client.Dispatch('Word.Application')

        # e.Visible=1
        # w.Visible=1

        try:
            wd = w.Documents.Open(word)
        except:
            dlg = wx.MessageDialog(self, 'open word %s failed ' % word,
                                   'error', wx.OK | wx.ICON_ERROR)
            dlg.ShowModal()
            dlg.Destroy()

            # raise WordExcelError("open word failed")

            raise
        try:
            eb = e.Workbooks.open(excel)
        except:
            dlg = wx.MessageDialog(self, 'open excel %s failed '
                                   % excel, 'error', wx.OK
                                   | wx.ICON_ERROR)
            dlg.ShowModal()
            dlg.Destroy()
            wd.Close()

            # raise WordExcelError('open excel failed')

            raise

        row = 4
        word_rows = wd.Tables(1).Rows.count
        while 1:
            row = row + 1
            if eb.Sheets(1).Cells(row, 9).value is None:
                break
            if len(eb.Sheets(1).Cells(row, 9).value) != 18 \
                and len(eb.Sheets(1).Cells(row, 9).value) != 15:
                dlg = wx.MessageDialog(self, 'ID number error on %d: %s'
                         % (row, eb.Sheets(1).Cells(row, 9).value),
                        'error', wx.OK | wx.ICON_ERROR)
                dlg.ShowModal()
                dlg.Destroy()
                wd.Save()
                wd.Close()
                eb.Close()
                raise WordExcelError('id number error on row %d' % row)

            if word_rows < row - 3:
                try:
                    wd.Tables(1).Rows.Add()
                    word_rows = wd.Tables(1).Rows.count
                except:
                    dlg = wx.MessageDialog(self, 'add row error',
                            'error', wx.OK | wx.ICON_ERROR)
                    dlg.ShowModal()
                    dlg.Destroy()
                    wd.Save()
                    wd.Close()
                    eb.Close()

                    # raise WordExcelError('add row error')

                    raise

            for cell in range(1, 10):
                try:
                    wd.Tables(1).Rows(row - 3).Cells(cell).Range.Text = \
                        eb.Sheets(1).Cells(row, cell)
                except:
                    dlg = wx.MessageDialog(self, 'write to word error',
                            'error', wx.OK | wx.ICON_ERROR)
                    dlg.ShowModal()
                    dlg.Destroy()
                    wd.Save()
                    wd.Close()
                    eb.Close()

                    # raise WordExcelError('write word error')

                    raise

        wd.Save()
        wd.Close()
        eb.Close()
        w.Quit()
        e.Quit()


class myapp(wx.App):

    def __init__(self):
        wx.App.__init__(self, 0)
        self.frame = myframe()
        self.frame.Show()
        self.SetTopWindow(self.frame)


        # self.MainLoop()

if __name__ == '__main__':
    app = myapp()
    app.MainLoop()

    # print "end"
