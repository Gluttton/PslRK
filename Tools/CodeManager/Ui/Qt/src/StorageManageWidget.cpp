#include "StorageManageWidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QDebug>



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

    QStringList tableCodesHeaders;
    tableCodesHeaders
        << tr ("ID")
        << tr ("Length")
        << tr ("MSL");
    modelCodes->setHorizontalHeaderLabels (tableCodesHeaders);
    modelCodes->setColumnCount (3);
    tableCodes->setModel (modelCodes);
    tableCodes->horizontalHeader ()->setSectionResizeMode (0, QHeaderView::Stretch);
    tableCodes->horizontalHeader ()->setSectionResizeMode (1, QHeaderView::Stretch);
    tableCodes->horizontalHeader ()->setSectionResizeMode (2, QHeaderView::Stretch);


    QStringList tableSequencesHeaders;
    tableSequencesHeaders
        << tr ("Sequence");
    modelSequences->setHorizontalHeaderLabels (tableSequencesHeaders);
    modelSequences->setColumnCount (1);
    tableSequences->setModel (modelSequences);
    tableSequences->horizontalHeader ()->setSectionResizeMode (0, QHeaderView::Stretch);

    QStringList tableReferencesHeaders;
    tableReferencesHeaders
        // TODO: Author and Article should be swaped.
        << tr ("Author")
        << tr ("Article")
        << tr ("Link");
    modelReferences->setHorizontalHeaderLabels (tableReferencesHeaders);
    modelReferences->setColumnCount (3);
    tableReferences->setModel (modelReferences);
    tableReferences->horizontalHeader ()->setSectionResizeMode (0, QHeaderView::Stretch);
    tableReferences->horizontalHeader ()->setSectionResizeMode (1, QHeaderView::Stretch);
    tableReferences->horizontalHeader ()->setSectionResizeMode (2, QHeaderView::Stretch);

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
        cellId->setEditable (false);
        cellId->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
        cellId->setCheckable (false);
        cellId->setEditable (false);
        cellId->setData (code.attribute ("id").value (), Qt::DisplayRole);

        QStandardItem * cellLength = new QStandardItem ();
        cellLength->setEditable (false);
        cellLength->setTextAlignment (Qt::AlignCenter);
        cellLength->setCheckable (false);
        cellLength->setEditable (false);
        cellLength->setData (code.attribute ("length").value (), Qt::DisplayRole);

        QStandardItem * cellMsl = new QStandardItem ();
        cellMsl->setEditable (false);
        cellMsl->setTextAlignment (Qt::AlignCenter);
        cellMsl->setCheckable (false);
        cellMsl->setEditable (false);

        QList <QStandardItem *> cells;
        cells.append (cellId);
        cells.append (cellLength);
        cells.append (cellMsl);
        cellMsl->setData (code.attribute ("maxpsl").value (), Qt::DisplayRole);

        int row {0};
        for (const auto & sequence : code.children ("sequence") ) {
            QStandardItem * cellSequence = new QStandardItem ();
            cellSequence->setEditable (false);
            cellSequence->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellSequence->setCheckable (false);
            cellSequence->setEditable (false);
            cellSequence->setData (sequence.text ().get (), Qt::DisplayRole);
            cellSequence->setData (1, Qt::UserRole + 1);
            cellId->setChild (row, 0, cellSequence);
            ++row;

            //qDebug () << sequence.text ().get ();
        }

        for (const auto & reference : code.children ("reference") ) {
            QStandardItem * cellAuthor = new QStandardItem ();
            cellAuthor->setEditable (false);
            cellAuthor->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellAuthor->setCheckable (false);
            cellAuthor->setEditable (false);
            cellAuthor->setData (reference.attribute ("author").value (), Qt::DisplayRole);
            cellAuthor->setData (2, Qt::UserRole + 1);

            QStandardItem * cellArticle = new QStandardItem ();
            cellArticle->setEditable (false);
            cellArticle->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellArticle->setCheckable (false);
            cellArticle->setEditable (false);
            cellArticle->setData (reference.attribute ("article").value (), Qt::DisplayRole);
            cellArticle->setData (2, Qt::UserRole + 1);

            QStandardItem * cellLink = new QStandardItem ();
            cellLink->setEditable (false);
            cellLink->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
            cellLink->setCheckable (false);
            cellLink->setEditable (false);
            cellLink->setData (reference.attribute ("link").value (), Qt::DisplayRole);
            cellLink->setData (2, Qt::UserRole + 1);

            cellId->setChild (row, 0, cellAuthor);
            cellId->setChild (row, 1, cellArticle);
            cellId->setChild (row, 2, cellLink);
            ++row;

            //qDebug () << reference.attribute ("author").value ();
            //qDebug () << reference.attribute ("article").value ();
            //qDebug () << reference.attribute ("link").value ();
        }

        modelCodes->appendRow (cells);
    }
}



void StorageManageWidget::onModelCodesSelectionChanged (QItemSelection selectedItem, QItemSelection deselectedItem)
{
    QModelIndex index = modelCodes->item (selectedItem.indexes ().first ().row (), 0)->index ();

    modelSequences->removeRows  (0, modelSequences->rowCount () );
    modelReferences->removeRows (0, modelReferences->rowCount () );

    for (int i = 0; i < modelCodes->itemFromIndex (index)->rowCount (); ++i) {
        if (modelCodes->data (modelCodes->index (i, 0, index), Qt::UserRole + 1) == 1) {
            QStandardItem * cell = new QStandardItem ();
            cell->setData (modelCodes->data (modelCodes->index (i, 0, index), Qt::DisplayRole), Qt::DisplayRole);
            QList <QStandardItem *> cells;
            cells.append (cell);
            modelSequences->appendRow (cells);
        }
        else if (modelCodes->data (modelCodes->index (i, 0, index), Qt::UserRole + 1) == 2) {
            QStandardItem * cellAuthor  = new QStandardItem ();
            QStandardItem * cellArticle = new QStandardItem ();
            QStandardItem * cellLink    = new QStandardItem ();
            cellAuthor->setData (modelCodes->data (modelCodes->index (i, 0, index), Qt::DisplayRole), Qt::DisplayRole);
            cellArticle->setData (modelCodes->data (modelCodes->index (i, 1, index), Qt::DisplayRole), Qt::DisplayRole);
            cellLink->setData (modelCodes->data (modelCodes->index (i, 2, index), Qt::DisplayRole), Qt::DisplayRole);
            QList <QStandardItem *> cells;
            cells.append (cellAuthor);
            cells.append (cellArticle);
            cells.append (cellLink);
            modelReferences->appendRow (cells);
        }
        else {
        }
    }
}