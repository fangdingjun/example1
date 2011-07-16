#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
//#include <qvbox.h>
#include <qlabel.h>
//#include <ui_myf.h>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QLabel label("<h1>hello,<font color=red>QT</font></h1>");
    //QPushButton quit("Quit", 0);
    //quit.resize(75, 30);
    //quit.setFont(QFont("Times", 18, QFont::Bold));
    //QObject::connect(&quit, SIGNAL(clicked()), &a, SLOT(quit()));
    //a.setMainWidget(&quit);
    //quit.show();
    label.show();
    return a.exec();
}
