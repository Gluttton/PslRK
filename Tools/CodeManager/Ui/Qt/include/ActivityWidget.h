#ifndef PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H
#define PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include "External/QCustomPlot/qcustomplot.h"



class ActivityWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ActivityWidget                 (QWidget * parent = nullptr);
        virtual ~ActivityWidget                 () = default;

    public slots:
        void onLengthAutoDetectChanged          (const int);
        void onHexViewEdited                    (const QString &);
        void onStringViewEdited                 (const QString &);
        void onViewChanged                      (const std::string &);

    private:
        void createWidgets                      ();
        void createLayouts                      ();
        void createConnections                  ();

        QLineEdit                             * editCodeId;
        QLineEdit                             * editLength;
        QLineEdit                             * editHexView;
        QLineEdit                             * editStringView;
        QLineEdit                             * editMsl;
        QCheckBox                             * checkLengthAuto;

        QCustomPlot                           * plot;

        bool                                    isLengthAutoDetect;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H
