#include "ActivityWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFontMetrics>



ActivityWidget::ActivityWidget (QWidget * parent)
            : QWidget           (parent)
            , plot              (nullptr)
{
    createWidgets       ();
    createLayouts       ();
    createConnections   ();
}



void ActivityWidget::createWidgets ()
{
    plot = new QCustomPlot (this);
}



void ActivityWidget::createLayouts ()
{
    QHBoxLayout * layoutCodeId = new QHBoxLayout ();
    QLabel * labelCodeId = new QLabel (tr ("Code ID") );
    QLineEdit * editCodeId = new QLineEdit ();
    layoutCodeId->addWidget (labelCodeId);
    layoutCodeId->addWidget (editCodeId);

    QHBoxLayout * layoutLength = new QHBoxLayout ();
    QLabel * labelLength = new QLabel (tr ("Length") );
    QLineEdit * editLength = new QLineEdit ();
    layoutLength->addWidget (labelLength);
    layoutLength->addWidget (editLength);

    QHBoxLayout * layoutHexView = new QHBoxLayout ();
    QLabel * labelHexView = new QLabel (tr ("Hex View") );
    QLineEdit * editHexView = new QLineEdit ();
    layoutHexView->addWidget (labelHexView);
    layoutHexView->addWidget (editHexView);

    QHBoxLayout * layoutStringView = new QHBoxLayout ();
    QLabel * labelStringView = new QLabel (tr ("String View") );
    QLineEdit * editStringView = new QLineEdit ();
    layoutStringView->addWidget (labelStringView);
    layoutStringView->addWidget (editStringView);

    int width {0};
    width = std::max (labelCodeId->fontMetrics     ().width (labelCodeId->text     () ), width);
    width = std::max (labelLength->fontMetrics     ().width (labelLength->text     () ), width);
    width = std::max (labelHexView->fontMetrics    ().width (labelHexView->text    () ), width);
    width = std::max (labelStringView->fontMetrics ().width (labelStringView->text () ), width);
    labelCodeId->setFixedWidth     (width);
    labelLength->setFixedWidth     (width);
    labelHexView->setFixedWidth    (width);
    labelStringView->setFixedWidth (width);

    QWidget * widgetCode = new QWidget ();
    QVBoxLayout * layoutCode  = new QVBoxLayout ();
    layoutCode->addLayout (layoutCodeId);
    layoutCode->addLayout (layoutLength);
    layoutCode->addLayout (layoutHexView);
    layoutCode->addLayout (layoutStringView);
    layoutCode->addStretch ();
    widgetCode->setLayout (layoutCode);

    QWidget * widgetChart = new QWidget ();
    QVBoxLayout * layoutChart = new QVBoxLayout ();
    layoutChart->addWidget (plot);
    widgetChart->setLayout (layoutChart);

    QSplitter * splitterTop = new QSplitter (Qt::Vertical, this);
    QVBoxLayout * layoutTop = new QVBoxLayout ();
    splitterTop->addWidget (widgetCode);
    splitterTop->addWidget (widgetChart);
    splitterTop->setStretchFactor (0, 0);
    splitterTop->setStretchFactor (1, 1);
    layoutTop->addWidget (splitterTop);

    this->setLayout (layoutTop);
}



void ActivityWidget::createConnections ()
{
}