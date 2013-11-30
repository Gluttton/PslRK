#ifndef PSLRK_TOOLS_CODE_MANAGER_UI_QT_MAIN_WIDGET_H
#define PSLRK_TOOLS_CODE_MANAGER_UI_QT_MAIN_WIDGET_H



#include <QWidget>
#include "StorageManageWidget.h"
#include "ActivityWidget.h"



class MainWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWidget                     (QWidget * parent = nullptr);
        virtual ~MainWidget                     ();

    protected:
        void createWidgets                      ();
        void createLayouts                      ();
        void createConnections                  ();

        StorageManageWidget                   * storageManageWidget;
        ActivityWidget                        * activityWidget;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_UI_QT_MAIN_WIDGET_H
