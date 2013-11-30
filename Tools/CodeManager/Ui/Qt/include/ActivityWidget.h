#ifndef PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H
#define PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H

#include <QWidget>
#include "External/QCustomPlot/qcustomplot.h"



class ActivityWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ActivityWidget                 (QWidget * parent = nullptr);
        virtual ~ActivityWidget                 () = default;

    private:
        void createWidgets                      ();
        void createLayouts                      ();
        void createConnections                  ();

        QCustomPlot                           * plot;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_UI_QT_ACTIVITY_WIDGET_H
