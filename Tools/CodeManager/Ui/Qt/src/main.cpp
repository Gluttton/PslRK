#include <QApplication>
#include "MainWidget.h"



int main (int argc, char * argv [])
{
    QApplication application (argc, argv);

    MainWidget mainWidget;
    mainWidget.showMaximized ();

    return application.exec ();
}
