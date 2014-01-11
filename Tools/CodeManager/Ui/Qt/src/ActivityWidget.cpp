#include "ActivityWidget.h"
#include "ValidatorAdapter.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFontMetrics>
#include <QVector>
#include <Calculator.h>
#include <Representer.h>
#include <QDebug>



ActivityWidget::ActivityWidget (QWidget * parent)
            : QWidget           (parent)
            , editCodeId        (nullptr)
            , editLength        (nullptr)
            , editHexView       (nullptr)
            , editStringView    (nullptr)
            , editPsl           (nullptr)
            , checkLengthAuto   (nullptr)
            , plot              (nullptr)
            , isLengthAutoDetect(true)
{
    createWidgets       ();
    createLayouts       ();
    createConnections   ();
}



void ActivityWidget::createWidgets ()
{
    editCodeId     = new QLineEdit (this);
    editLength     = new QLineEdit (this);
    editHexView    = new QLineEdit (this);
    editStringView = new QLineEdit (this);
    editPsl        = new QLineEdit (this);

    editHexView->setValidator    (new ValidatorHexViewAdapter);
    editStringView->setValidator (new ValidatorStringViewAdapter);
    editStringView->setReadOnly  (!isLengthAutoDetect);

    checkLengthAuto = new QCheckBox (this);
    checkLengthAuto->setCheckState (isLengthAutoDetect ? Qt::Checked : Qt::Unchecked);
    
    plot = new QCustomPlot (this);
}



void ActivityWidget::createLayouts ()
{
    QHBoxLayout * layoutCodeId = new QHBoxLayout ();
    QLabel * labelCodeId = new QLabel (tr ("Code ID") );
    layoutCodeId->addWidget (labelCodeId);
    layoutCodeId->addWidget (editCodeId);

    QHBoxLayout * layoutLength = new QHBoxLayout ();
    QLabel * labelLength = new QLabel (tr ("Length") );
    layoutLength->addWidget (labelLength);
    layoutLength->addWidget (editLength);
    QLabel * labelLengthAuto = new QLabel (tr ("Auto detect") );
    layoutLength->addWidget (labelLengthAuto);
    layoutLength->addWidget (checkLengthAuto);

    QHBoxLayout * layoutHexView = new QHBoxLayout ();
    QLabel * labelHexView = new QLabel (tr ("Hex View") );
    layoutHexView->addWidget (labelHexView);
    layoutHexView->addWidget (editHexView);

    QHBoxLayout * layoutStringView = new QHBoxLayout ();
    QLabel * labelStringView = new QLabel (tr ("String View") );
    layoutStringView->addWidget (labelStringView);
    layoutStringView->addWidget (editStringView);

    QHBoxLayout * layoutPsl = new QHBoxLayout ();
    QLabel * labelPsl = new QLabel (tr ("PSL") );
    layoutPsl->addWidget (labelPsl);
    layoutPsl->addWidget (editPsl);

    int width {0};
    width = std::max (labelCodeId->fontMetrics     ().width (labelCodeId->text     () ), width);
    width = std::max (labelLength->fontMetrics     ().width (labelLength->text     () ), width);
    width = std::max (labelHexView->fontMetrics    ().width (labelHexView->text    () ), width);
    width = std::max (labelStringView->fontMetrics ().width (labelStringView->text () ), width);
    width = std::max (labelPsl->fontMetrics        ().width (labelPsl->text        () ), width);
    labelCodeId->setFixedWidth     (width);
    labelLength->setFixedWidth     (width);
    labelHexView->setFixedWidth    (width);
    labelStringView->setFixedWidth (width);
    labelPsl->setFixedWidth        (width);

    QWidget * widgetCode = new QWidget ();
    QVBoxLayout * layoutCode  = new QVBoxLayout ();
    layoutCode->addLayout (layoutCodeId);
    layoutCode->addLayout (layoutLength);
    layoutCode->addLayout (layoutHexView);
    layoutCode->addLayout (layoutStringView);
    layoutCode->addLayout (layoutPsl);
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
    connect (editHexView,     SIGNAL (textEdited   (const QString &) ), this, SLOT (onHexViewEdited    (const QString &) ) );
    connect (editStringView,  SIGNAL (textEdited   (const QString &) ), this, SLOT (onStringViewEdited (const QString &) ) );
    connect (checkLengthAuto, SIGNAL (stateChanged (int) ),             this, SLOT (onLengthAutoDetectChanged (const int) ) );
}



void ActivityWidget::onLengthAutoDetectChanged (const int state)
{
    isLengthAutoDetect = (state == Qt::Checked ? true : false);

    // Explicit setting of code length has sense only for manipulating with hex views.
    editStringView->setReadOnly (!isLengthAutoDetect);
}



void ActivityWidget::onHexViewEdited (const QString & view)
{
    std::string stringView;
    if (isLengthAutoDetect) {
        stringView = Pslrk::Core::Representer::HexViewToStringView (view.toStdString () );
    }
    else {
        stringView = Pslrk::Core::Representer::HexViewToStringView (view.toStdString (), editLength->text ().toInt () );
    }

    onViewChanged (stringView);

    editStringView->setText (QString::fromStdString (stringView) );
}



void ActivityWidget::onStringViewEdited (const QString & view)
{
    onViewChanged (view.toStdString () );

    editHexView->setText (QString::fromStdString (Pslrk::Core::Representer::StringViewToHexView(view.toStdString () ) ) );
}



void ActivityWidget::onViewChanged (const std::string & view)
{
    editCodeId->setText (QString::fromStdString (Pslrk::Core::Representer::DetectCodeId (view) ) );
    editPsl->setText    (QString ("%1").arg (Pslrk::Core::Calculator::CalculatePsl (view) ) );
    if (isLengthAutoDetect) {
        editLength->setText (QString ("%1").arg (view.size () ) );
    }

    const double range = view.size ();

    QVector <double> y;
    for (auto i : Pslrk::Core::Calculator::CalculateAcf (view) ) {
        y.push_back (i);
    }
    QVector <double> x;
    for (int i = 0; i < y.size (); ++i) {
        x.push_back (i - range + 1);
    }

    double min {0.0};
    for (auto i : y) {
        min = std::min (min, i);
    }
    double max {0.0};
    for (auto i : y) {
        max = std::max (max, i);
    }

    plot->addGraph ();
    plot->graph (0)->setData (x, y);
    plot->graph (0)->setPen (QPen (Qt::blue) );
    plot->xAxis->setRange (-range, range);
    plot->yAxis->setRange (   min, max);
    plot->xAxis->setVisible (true);
    plot->yAxis->setVisible (true);
    plot->replot ();
}