#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import wx


class main_frame(wx.Frame):

    def __init__(
        self,
        parent,
        id,
        title,
        ):
        ctrls = []
        wx.Frame.__init__(self, parent, id, title, size=(350, 210))
        panel = wx.Panel(self, -1)
        lbl1 = wx.StaticText(panel, -1, 'Select image directory:')
        self.img_dir = wx.TextCtrl(panel, -1, size=(200, -1))
        dir_o = wx.Button(panel, -1, 'browse', size=(50, -1))
        lbl2 = wx.StaticText(panel, -1, 'Select Excel file to save:')
        self.e_file = wx.TextCtrl(panel, -1, size=(200, -1))
        file_o = wx.Button(panel, -1, 'browse', size=(50, -1))
        bn = wx.Button(panel, -1, 'ok', size=(40, -1))
        bn_x = wx.Button(panel, -1, 'exit', size=(40, -1))

        self.Bind(wx.EVT_BUTTON, self.on_close, bn_x)
        self.Bind(wx.EVT_BUTTON, self.selectdir, dir_o)
        self.Bind(wx.EVT_BUTTON, self.selectfile, file_o)
        self.Bind(wx.EVT_BUTTON, self.insert_img_to_excel, bn)

        sizer = wx.BoxSizer(wx.VERTICAL)

        s = wx.BoxSizer(wx.HORIZONTAL)
        s.Add((50, -1))
        s.Add(lbl1)
        sizer.Add(s, 0, wx.ALIGN_LEFT)
        sizer.Add((-1, 5))

        s = wx.BoxSizer(wx.HORIZONTAL)
        s.Add((50, -1))
        s.Add(self.img_dir)
        s.Add(dir_o)
        sizer.Add(s, 0, wx.ALIGN_LEFT)

        s = wx.BoxSizer(wx.HORIZONTAL)
        s.Add((50, -1))
        s.Add(lbl2)
        sizer.Add((-1, 10))
        sizer.Add(s, 0, wx.ALIGN_LEFT)
        sizer.Add((-1, 5))

        s = wx.BoxSizer(wx.HORIZONTAL)
        s.Add((50, -1))
        s.Add(self.e_file)
        s.Add(file_o)
        sizer.Add(s, 0, wx.ALIGN_LEFT)

        s = wx.BoxSizer(wx.HORIZONTAL)
        s.Add((100, -1))
        s.Add(bn)
        s.Add((30, -1))
        s.Add(bn_x)
        s.Add((30, -1))
        sizer.Add((-1, 5))
        sizer.Add(s, 0, wx.ALIGN_LEFT)
        panel.SetSizer(sizer)
        sizer.Fit(panel)
        panel.Fit()
        self.createmenu()
        self.createstatusbar()

    def createmenu(self):
        menubar = wx.MenuBar()
        m = wx.Menu()
        e = m.Append(-1, 'Quit\tAlt-X')
        self.Bind(wx.EVT_MENU, self.on_close, e)
        menubar.Append(m, 'File')
        self.SetMenuBar(menubar)

    def createstatusbar(self):
        statusbar = wx.StatusBar(self)
        self.SetStatusBar(statusbar)

    def on_close(self, event):
        self.Close()

    def selectdir(self, event):
        dlg = wx.DirDialog(self, 'Choose a directory:')
        if dlg.ShowModal() == wx.ID_OK:
            self.img_dir.Clear()
            self.img_dir.WriteText(dlg.GetPath())
        dlg.Destroy()

    def selectfile(self, event):
        dlg = wx.FileDialog(self, message='Save file as ...',
                            defaultFile='img.xls',
                            wildcard='Excel file(*.xls)|*.xls|All files(*.*)|*.*'
                            , style=wx.SAVE)
        if dlg.ShowModal() == wx.ID_OK:
            self.e_file.Clear()
            self.e_file.WriteText(dlg.GetPath())
        dlg.Destroy()

    def insert_img_to_excel(self, event):
        img_dir = self.img_dir.GetValue()
        file_name = self.e_file.GetValue()
        if img_dir == '' or file_name == '':
            wx.MessageBox('Please select image director or Excel file\n'
                          , 'ERROR', wx.ICON_ERROR)
            return False
        from glob import glob
        import win32com.client
        imgs = glob(img_dir + '\\*.jpg')
        if len(imgs) < 1:
            wx.MessageBox('There is no .jpg files in %s' % img_dir,
                          'ERROR', wx.ICON_ERROR)
            return False

        e = win32com.client.Dispatch('Excel.application')
        e.Visible = 1
        wb = e.Workbooks.Add()
        sh = wb.Sheets(1)
        p = sh.Pictures()
        try:
            a = 1
            i = 1
            j = 1
            for f in imgs:
                sh.Cells(i, a).Select()
                i = p.Insert(f)
                i.ShapeRange.LockAspectRatio = True
                i.ShapeRange.Width = 200
                i.ShapeRange.Height = 200
                a = a + 4
                j = j + 1
                if j % 4 == 0:
                    i = i + 4
                    a = 1
            wb.SaveAs(file_name)
        except:
            pass
        finally:
            e.Visible = 0
            e.Visible = 1


class main_app(wx.App):

    def OnInit(self):
        self.f = main_frame(None, -1, 'load image to excel')
        self.f.Center()
        self.f.Show()
        return True


if __name__ == '__main__':
    app = main_app(0)
    app.MainLoop()
