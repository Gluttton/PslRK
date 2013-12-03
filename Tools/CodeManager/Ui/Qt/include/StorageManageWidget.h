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

        static const int                        columnCountTableCodes       {3};
        static const int                        columnCountTableSequences   {1};
        static const int                        columnCountTableReferences  {3};
        static const int                        columnNumberId              {0};
        static const int                        columnNumberLength          {1};
        static const int                        columnNumberMsl             {2};
        static const int                        columnNumberSequence        {0};
        static const int                        columnNumberArticle         {0};
        static const int                        columnNumberAuthor          {1};
        static const int                        columnNumberLink            {2};
        static const int                        DataTypeRole                {Qt::UserRole + 1};
        static const int                        DataTypeSequence            {1};
        static const int                        DataTypeReference           {2};
};

#endif//PSLRK_TOOLS_CODE_MANAGER_UI_QT_STORAGE_MANAGE_WIDGET_H
