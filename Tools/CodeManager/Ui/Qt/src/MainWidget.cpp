#include "MainWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>



MainWidget::MainWidget (QWidget * parent)
            : QWidget               (parent)
            , storageManageWidget   (nullptr)
            , activityWidget        (nullptr)
{
    createWidgets       ();
    createLayouts       ();
    createConnections   ();
}



MainWidget::~MainWidget ()
{
}



void MainWidget::createWidgets ()
{
    setWindowTitle (tr ("CodeManager") );

    storageManageWidget = new StorageManageWidget (this);
    activityWidget      = new ActivityWidget      (this);
}



void MainWidget::createLayouts ()
{
    QSplitter * splitterTop = new QSplitter (Qt::Horizontal, this);
    splitterTop->addWidget (storageManageWidget);
    splitterTop->addWidget (activityWidget);
    splitterTop->setStretchFactor (0, 1);
    splitterTop->setStretchFactor (1, 1);

    QHBoxLayout * layoutTop = new QHBoxLayout ();
    layoutTop->addWidget (splitterTop);
    this->setLayout      (layoutTop);
}



void MainWidget::createConnections ()
{
}