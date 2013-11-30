#ifndef PSLRK_TOOLS_CODE_MANAGER_UI_QT_STORAGE_MANAGE_WIDGET_H
#define PSLRK_TOOLS_CODE_MANAGER_UI_QT_STORAGE_MANAGE_WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QStandardItemModel>
#include <XmlManager.h>



class StorageManageWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit StorageManageWidget            (QWidget * parent = nullptr);
        virtual ~StorageManageWidget            ();

    private slots:
        void onDataSourceBrowsing               ();
        void onDataSourceOpening                ();
        void onModelCodesSelectionChanged       (QItemSelection, QItemSelection);

    private:
        void createWidgets                      ();
        void createLayouts                      ();
        void createConnections                  ();

        QTableView                            * tableCodes;
        QTableView                            * tableSequences;
        QTableView                            * tableReferences;

        QStandardItemModel                    * modelCodes;
        QStandardItemModel                    * modelSequences;
        QStandardItemModel                    * modelReferences;

        QPushButton                           * buttonDataSourceOpen;
        QPushButton                           * buttonDataSourceBrowse;
        QLineEdit                             * editDataSource;

        Pslrk::Core::XmlManager               * xmlManager;
};

#endif//PSLRK_TOOLS_CODE_MANAGER_UI_QT_STORAGE_MANAGE_WIDGET_H
