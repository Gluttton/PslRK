#include "StorageManageWidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFileDialog>



StorageManageWidget::StorageManageWidget (QWidget * parent)
            : QWidget                   (parent)
            , tableCodes                (nullptr)
            , tableSequences            (nullptr)
            , tableReferences           (nullptr)
            , modelCodes                (nullptr)
            , modelSequences            (nullptr)
            , modelReferences           (nullptr)
            , buttonDataSourceOpen      (nullptr)
            , buttonDataSourceBrowse    (nullptr)
            , editDataSource            (nullptr)
            , xmlManager                (nullptr)
{
    createWidgets       ();
    createLayouts       ();
    createConnections   ();
}



StorageManageWidget::~StorageManageWidget ()
{
    delete xmlManager;
}



void StorageManageWidget::createWidgets ()
{
    tableCodes      = new QTableView (this);
    tableSequences  = new QTableView (this);
    tableReferences = new QTableView (this);

    modelCodes      = new QStandardItemModel (this);
    modelSequences  = new QStandardItemModel (this);
    modelReferences = new QStandardItemModel (this);

    modelCodes->setHorizontalHeaderLabels ({tr ("ID"), tr ("Length"), tr ("MSL")});
    modelCodes->setColumnCount (columnCountTableCodes);
    tableCodes->setModel (modelCodes);
    tableCodes->horizontalHeader ()->setSectionResizeMode (columnNumberId,     QHeaderView::Stretch);
    tableCodes->horizontalHeader ()->setSectionResizeMode (columnNumberLength, QHeaderView::Stretch);
    tableCodes->horizontalHeader ()->setSectionResizeMode (columnNumberMsl,    QHeaderView::Stretch);

    modelSequences->setHorizontalHeaderLabels ({tr ("Sequence")});
    modelSequences->setColumnCount (columnCountTableSequences);
    tableSequences->setModel (modelSequences);
    tableSequences->horizontalHeader ()->setSectionResizeMode (columnNumberSequence, QHeaderView::Stretch);

    modelReferences->setHorizontalHeaderLabels ({tr ("Article"), tr ("Author"), tr ("Link")});
    modelReferences->setColumnCount (columnCountTableReferences);
    tableReferences->setModel (modelReferences);
    tableReferences->horizontalHeader ()->setSectionResizeMode (columnNumberArticle, QHeaderView::Stretch);
    tableReferences->horizontalHeader ()->setSectionResizeMode (columnNumberAuthor,  QHeaderView::Stretch);
    tableReferences->horizontalHeader ()->setSectionResizeMode (columnNumberLink,    QHeaderView::Stretch);

    buttonDataSourceBrowse = new QPushButton (tr ("..."), this);
    buttonDataSourceOpen   = new QPushButton (tr ("Open"), this);
    editDataSource         = new QLineEdit   (this);
}



void StorageManageWidget::createLayouts ()
{
    QHBoxLayout * layoutDataSource = new QHBoxLayout ();
    layoutDataSource->addWidget (editDataSource);
    layoutDataSource->addWidget (buttonDataSourceBrowse);
    layoutDataSource->addWidget (buttonDataSourceOpen);

    QVBoxLayout * layoutTop = new QVBoxLayout ();
    layoutTop->addLayout (layoutDataSource);
    layoutTop->addWidget (tableCodes);
    layoutTop->addWidget (tableSequences);
    layoutTop->addWidget (tableReferences);
    this->setLayout (layoutTop);
}



void StorageManageWidget::createConnections ()
{
    connect (buttonDataSourceBrowse, SIGNAL (clicked () ), this, SLOT (onDataSourceBrowsing () ) );
    connect (buttonDataSourceOpen,   SIGNAL (clicked () ), this, SLOT (onDataSourceOpening  () ) );
    connect (tableCodes->selectionModel (), SIGNAL (selectionChanged (QItemSelection, QItemSelection) ), this, SLOT (onModelCodesSelectionChanged (QItemSelection, QItemSelection) ) );
}



void StorageManageWidget::onDataSourceBrowsing ()
{
    QFileDialog dialog;
    dialog.setFileMode (QFileDialog::AnyFile);
    editDataSource->setText (dialog.getOpenFileName () );
}



void StorageManageWidget::onDataSourceOpening ()
{
    xmlManager = new Pslrk::Core::XmlManager (editDataSource->text ().toStdString () );
    
    const pugi::xml_node codes = xmlManager->Select ("/").node ();
    for (const auto & code : codes.child ("codes").children ("code") ) {
        QStandardItem * cellId = new QStandardItem ();
        cellId->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
        cellId->setEditable (false);
        cellId->setData (code.attribute ("id").value (), Qt::DisplayRole);

        QStandardItem * cellLength = new QStandardItem ();
        cellLength->setTextAlignment (Qt::AlignCenter);
        cellLength->setEditable (false);
        cellLength->setData (code.attribute ("length").value (), Qt::DisplayRole);

        QStandardItem * cellMsl = new QStandardItem ();
        cellMsl->setTextAlignment (Qt::AlignCenter);
        cellMsl->setEditable (false);
        cellMsl->setData (code.attribute ("maxpsl").value (), Qt::DisplayRole);

        QList <QStandardItem *> cells {cellId, cellLength, cellMsl};

        int row {0};
        for (const auto & sequence : code.children ("sequence") ) {
            QStandardItem * cellSequence = new QStandardItem ();
            cellSequence->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellSequence->setData (sequence.text ().get (), Qt::DisplayRole);
            cellSequence->setData (DataTypeSequence, DataTypeRole);
            cellId->setChild (row, columnNumberId, cellSequence);
            ++row;
        }

        for (const auto & reference : code.children ("reference") ) {
            QStandardItem * cellAuthor = new QStandardItem ();
            cellAuthor->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellAuthor->setData (reference.attribute ("author").value (), Qt::DisplayRole);
            cellAuthor->setData (DataTypeReference, DataTypeRole);

            QStandardItem * cellArticle = new QStandardItem ();
            cellArticle->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellArticle->setData (reference.attribute ("article").value (), Qt::DisplayRole);
            cellArticle->setData (DataTypeReference, DataTypeRole);

            QStandardItem * cellLink = new QStandardItem ();
            cellLink->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellLink->setData (reference.attribute ("link").value (), Qt::DisplayRole);
            cellLink->setData (DataTypeReference, DataTypeRole);

            cellId->setChild (row, columnNumberArticle, cellArticle);
            cellId->setChild (row, columnNumberAuthor,  cellAuthor);
            cellId->setChild (row, columnNumberLink,    cellLink);
            ++row;
        }

        modelCodes->appendRow (cells);
    }
}



void StorageManageWidget::onModelCodesSelectionChanged (QItemSelection selectedItem, QItemSelection deselectedItem)
{
    QModelIndex index = modelCodes->item (selectedItem.indexes ().first ().row (), columnNumberId)->index ();

    modelSequences->removeRows  (0, modelSequences->rowCount  () );
    modelReferences->removeRows (0, modelReferences->rowCount () );

    for (int i = 0; i < modelCodes->itemFromIndex (index)->rowCount (); ++i) {
        switch (modelCodes->data (modelCodes->index (i, columnNumberId, index), DataTypeRole).toInt () ) {
            case DataTypeSequence:
            {
                QStandardItem * cell = new QStandardItem ();
                cell->setData (modelCodes->data (modelCodes->index (i, columnNumberId, index), Qt::DisplayRole), Qt::DisplayRole);
                modelSequences->appendRow ({cell});
                break;
            }
            case DataTypeReference:
            {
                QStandardItem * cellAuthor  = new QStandardItem ();
                QStandardItem * cellArticle = new QStandardItem ();
                QStandardItem * cellLink    = new QStandardItem ();
                cellArticle->setData (modelCodes->data (modelCodes->index (i, columnNumberArticle, index), Qt::DisplayRole), Qt::DisplayRole);
                cellAuthor->setData  (modelCodes->data (modelCodes->index (i, columnNumberAuthor,  index), Qt::DisplayRole), Qt::DisplayRole);
                cellLink->setData    (modelCodes->data (modelCodes->index (i, columnNumberLink,    index), Qt::DisplayRole), Qt::DisplayRole);
                modelReferences->appendRow ({cellArticle, cellAuthor, cellLink});
                break;
            }
        }
    }
}