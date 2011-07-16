#include <wx/wx.h>

class MyApp:public wxApp {
    virtual bool OnInit();
};

class MyFrame:public wxFrame {
  public:
    MyFrame(const wxString & title, const wxPoint & pos,
            const wxSize & size);
    void OnQuit(wxCommandEvent & event);
    void OnAbout(wxCommandEvent & event);
     DECLARE_EVENT_TABLE();
};

enum {
    ID_Quit = 1,
    ID_About,
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit, MyFrame::OnQuit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
END_EVENT_TABLE()


bool MyApp::OnInit()
{
    MyFrame *frame =
        new MyFrame(_T("hello world"), wxPoint(50, 50), wxSize(450, 450));
    frame -> Show(true);
    SetTopWindow(frame);
    return true;
}

MyFrame::MyFrame(const wxString & title, const wxPoint & pos, const wxSize & size):wxFrame(NULL, -1, title, pos,
        size)
{
    wxMenu *menufile = new wxMenu;
    menufile->Append(ID_About, _T("&about.."));
    menufile->AppendSeparator();
    menufile->Append(ID_Quit, _T("E&xit"));
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menufile, _T("&file"));
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText(_T("welcome to wxWidgets"));
}

void MyFrame::OnQuit(wxCommandEvent & event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent & event)
{
    wxMessageBox(_T("this is a simple hello sample"), _T("about hello world"),
                 wxOK | wxICON_INFORMATION, this);
}

IMPLEMENT_APP(MyApp)
