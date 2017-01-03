#ifndef PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H
#define PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <qcustomplot.h>



class ActivityWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ActivityWidget                 (QWidget * parent = nullptr);
        virtual ~ActivityWidget                 () = default;

    public slots:
        void onLengthEdited                     (const QString &);
        void onLengthAutoDetectChanged          (const int);
        void onHexViewEdited                    (const QString &);
        void onStringViewEdited                 (const QString &);
        void onViewChanged                      (const std::string &);
        void onCodeSubstituting                 (const QString &);

    private:
        void createWidgets                      ();
        void createLayouts                      ();
        void createConnections                  ();

        QLineEdit                             * editCodeId;
        QLineEdit                             * editLength;
        QLineEdit                             * editHexView;
        QLineEdit                             * editStringView;
        QLineEdit                             * editFilter;
        QLineEdit                             * editMl;
        QLineEdit                             * editPsl;
        QLineEdit                             * editDb;
        QLineEdit                             * editE;
        QLineEdit                             * editMf;
        QLineEdit                             * editIsl;
        QCheckBox                             * checkLengthAuto;
        QCheckBox                             * checkFilterMatched;
        QCheckBox                             * checkShowAbs;

        QCustomPlot                           * plot;

        bool                                    isLengthAutoDetect;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H
