#include "ActivityWidget.h"
#include "ValidatorAdapter.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFontMetrics>
#include <QVector>
#include <QIntValidator>
#include <Calculator.h>
#include <Representer.h>
#include <QDebug>



ActivityWidget::ActivityWidget (QWidget * parent)
            : QWidget           (parent)
            , editCodeId        (nullptr)
            , editLength        (nullptr)
            , editHexView       (nullptr)
            , editStringView    (nullptr)
            , editFilter        (nullptr)
            , editMl            (nullptr)
            , editPsl           (nullptr)
            , checkLengthAuto   (nullptr)
            , checkFilterMatched(nullptr)
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
    editFilter     = new QLineEdit (this);
    editMl         = new QLineEdit (this);
    editPsl        = new QLineEdit (this);
    editDb         = new QLineEdit (this);
    editE          = new QLineEdit (this);
    editMf         = new QLineEdit (this);
    editIsl        = new QLineEdit (this);

    editCodeId->setReadOnly      (true);
    editLength->setValidator     (new QIntValidator);
    editLength->setReadOnly      (isLengthAutoDetect);
    editHexView->setValidator    (new ValidatorHexViewAdapter);
    editStringView->setValidator (new ValidatorStringViewAdapter);
    editStringView->setReadOnly  (!isLengthAutoDetect);
    editFilter->setValidator     (new ValidatorStringViewAdapter);
    editFilter->setDisabled      (true);
    editMl->setReadOnly          (true);
    editPsl->setReadOnly         (true);
    editDb->setReadOnly          (true);
    editE->setReadOnly           (true);
    editMf->setReadOnly          (true);
    editIsl->setReadOnly         (true);

    checkLengthAuto    = new QCheckBox (this);
    checkFilterMatched = new QCheckBox (this);

    checkLengthAuto->setCheckState (isLengthAutoDetect ? Qt::Checked : Qt::Unchecked);
    checkFilterMatched->setCheckState (Qt::Checked);

    plot = new QCustomPlot (this);
    plot->addGraph ();
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

    QHBoxLayout * layoutFilter = new QHBoxLayout ();
    QLabel * labelFilter = new QLabel (tr ("Filter") );
    layoutFilter->addWidget (labelFilter);
    layoutFilter->addWidget (editFilter);
    QLabel * labelFilterMatched = new QLabel (tr ("Use matched filter") );
    layoutFilter->addWidget (labelFilterMatched);
    layoutFilter->addWidget (checkFilterMatched);

    QHBoxLayout * layoutFeatures = new QHBoxLayout ();
    QLabel * labelMl = new QLabel (tr ("ML") );
    layoutFeatures->addWidget (labelMl);
    layoutFeatures->addWidget (editMl);
    QLabel * labelPsl = new QLabel (tr ("PSL") );
    layoutFeatures->addWidget (labelPsl);
    layoutFeatures->addWidget (editPsl);
    QLabel * labelDb = new QLabel (tr ("dB") );
    layoutFeatures->addWidget (labelDb);
    layoutFeatures->addWidget (editDb);
    QLabel * labelE = new QLabel (tr ("Energy") );
    layoutFeatures->addWidget (labelE);
    layoutFeatures->addWidget (editE);
    QLabel * labelMf = new QLabel (tr ("Merit factor") );
    layoutFeatures->addWidget (labelMf);
    layoutFeatures->addWidget (editMf);
    QLabel * labelIsl = new QLabel (tr ("ISL") );
    layoutFeatures->addWidget (labelIsl);
    layoutFeatures->addWidget (editIsl);

    int width {0};
    width = std::max (labelCodeId->fontMetrics     ().width (labelCodeId->text     () ), width);
    width = std::max (labelLength->fontMetrics     ().width (labelLength->text     () ), width);
    width = std::max (labelHexView->fontMetrics    ().width (labelHexView->text    () ), width);
    width = std::max (labelStringView->fontMetrics ().width (labelStringView->text () ), width);
    width = std::max (labelFilter->fontMetrics     ().width (labelFilter->text     () ), width);
    width = std::max (labelMl->fontMetrics         ().width (labelMl->text         () ), width);
    labelCodeId->setFixedWidth     (width);
    labelLength->setFixedWidth     (width);
    labelHexView->setFixedWidth    (width);
    labelStringView->setFixedWidth (width);
    labelFilter->setFixedWidth     (width);
    labelMl->setFixedWidth        (width);

    QWidget * widgetCode = new QWidget ();
    QVBoxLayout * layoutCode  = new QVBoxLayout ();
    layoutCode->addLayout (layoutCodeId);
    layoutCode->addLayout (layoutLength);
    layoutCode->addLayout (layoutHexView);
    layoutCode->addLayout (layoutStringView);
    layoutCode->addLayout (layoutFilter);
    layoutCode->addLayout (layoutFeatures);
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
    connect (editLength,      SIGNAL (textEdited   (const QString &) ), this, SLOT (onLengthEdited     (const QString &) ) );
    connect (editHexView,     SIGNAL (textEdited   (const QString &) ), this, SLOT (onHexViewEdited    (const QString &) ) );
    connect (editStringView,  SIGNAL (textEdited   (const QString &) ), this, SLOT (onStringViewEdited (const QString &) ) );
    connect (checkLengthAuto, SIGNAL (stateChanged (int) ),             this, SLOT (onLengthAutoDetectChanged (const int) ) );
    connect (editFilter, & QLineEdit::textEdited, [this](){
        onStringViewEdited (editStringView->text () );
    });
    connect (checkFilterMatched, & QCheckBox::stateChanged, [this](const int state){
        editFilter->setDisabled (state);
        onStringViewEdited (editStringView->text () );
    });
}



void ActivityWidget::onLengthEdited (const QString &)
{
    onHexViewEdited (editHexView->text () );
}



void ActivityWidget::onLengthAutoDetectChanged (const int state)
{
    isLengthAutoDetect = (state == Qt::Checked ? true : false);

    editLength->setReadOnly     (isLengthAutoDetect);
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

    if (isLengthAutoDetect) {
        editLength->setText (QString ("%1").arg (view.size () ) );
    }

    double range {0.0};
    std::vector <int> convolution;

    if (checkFilterMatched->isChecked () ) {
        editMl->setText     (QString ("%1").arg (Pslrk::Core::Calculator::Ml  (view) ) );
        editPsl->setText    (QString ("%1").arg (Pslrk::Core::Calculator::Psl (view) ) );
        editDb->setText     (QString::number (
            Pslrk::Core::Calculator::Db (
                Pslrk::Core::Calculator::Ml  (view),
                Pslrk::Core::Calculator::Psl (view)
            ),
            'f',
            3       // Only three digits after period must be displayed.
        ) );
        editE->setText      (QString ("%1").arg (Pslrk::Core::Calculator::E (view) ) );
        editMf->setText     (QString::number (
            Pslrk::Core::Calculator::Mf (view),
            'f',
            3       // Only three digits after period must be displayed.
        ) );
        editE->setText      (QString ("%1").arg (Pslrk::Core::Calculator::E (view) ) );
        editIsl->setText    (QString::number (
            Pslrk::Core::Calculator::Isl (view),
            'f',
            3       // Only three digits after period must be displayed.
        ) );

        convolution = Pslrk::Core::Calculator::Acf (view);
        range       = view.size () - 1.0;
    }
    else {
        const auto viewFilter = editFilter->text ().toStdString ();
        editMl->setText     (QString ("%1").arg (Pslrk::Core::Calculator::Ml  (view, viewFilter) ) );
        editPsl->setText    (QString ("%1").arg (Pslrk::Core::Calculator::Psl (view, viewFilter) ) );
        editDb->setText     (QString::number (
            Pslrk::Core::Calculator::Db (
                Pslrk::Core::Calculator::Ml  (view, viewFilter),
                Pslrk::Core::Calculator::Psl (view, viewFilter)
            ),
            'f',
            3       // Only three digits after period must be displayed.
        ) );
        editE->setText      (QString ("%1").arg (Pslrk::Core::Calculator::E (view, viewFilter) ) );
        editMf->setText     (QString::number (
            Pslrk::Core::Calculator::Mf (view, viewFilter),
            'f',
            3       // Only three digits after period must be displayed.
        ) );
        editE->setText      (QString ("%1").arg (Pslrk::Core::Calculator::E (view, viewFilter) ) );
        editIsl->setText    (QString::number (
            Pslrk::Core::Calculator::Isl (view, viewFilter),
            'f',
            3       // Only three digits after period must be displayed.
        ) );

        convolution = Pslrk::Core::Calculator::Ccf (view, editFilter->text ().toStdString () );
        range       = (view.size () + editFilter->text ().size () ) / 2.0 - 1.0;
    }

    QVector <double> y = QVector <double>::fromStdVector (std::vector <double> (convolution.begin (), convolution.end () ) );
    QVector <double> x;
    for (int i = 0; i < y.size (); ++i) {
        x.push_back (i - range);
    }

    const double min = * std::min_element (y.constBegin (), y.constEnd () ) - 1.0;
    const double max = * std::max_element (y.constBegin (), y.constEnd () ) + 1.0;

    plot->graph (0)->setData (x, y);
    plot->graph (0)->setPen (QPen (Qt::blue) );
    plot->xAxis->setRange (-range, range);
    plot->yAxis->setRange (   min, max);
    plot->xAxis->setVisible (true);
    plot->yAxis->setVisible (true);
    plot->replot ();
}



void ActivityWidget::onCodeSubstituting (const QString & stringView)
{
    // HACK: Ugly hack for implicit emmit textEdited.
    //       Needed for update all fields by data from editStringView.
    editStringView->clear  ();
    editStringView->insert (stringView);
}
