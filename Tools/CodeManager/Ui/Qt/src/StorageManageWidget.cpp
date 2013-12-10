#include "StorageManageWidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QLabel>
#include <QApplication>
#include <QDebug>



StorageManageWidget::StorageManageWidget (QWidget * parent)
            : QWidget                   (parent)
            , tableCodes                (nullptr)
            , tableSequences            (nullptr)
            , tableReferences           (nullptr)
            , modelCodes                (nullptr)
            , modelSequences            (nullptr)
            , modelReferences           (nullptr)
            , tableFocused              (nullptr)
            , buttonDataSourceOpen      (nullptr)
            , buttonDataSourceClose     (nullptr)
            , buttonDataSourceBrowse    (nullptr)
            , buttonDataSave            (nullptr)
            , buttonItemAdd             (nullptr)
            , buttonItemRemove          (nullptr)
            , editDataSource            (nullptr)
            , xmlManager                (nullptr)
{
    createWidgets       ();
    createLayouts       ();
    createConnections   ();
}



StorageManageWidget::~StorageManageWidget ()
{
    onDataSourceClosing ();

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

    buttonDataSourceBrowse = new QPushButton (tr ("..."),    this);
    buttonDataSourceOpen   = new QPushButton (tr ("Open"),   this);
    buttonDataSourceClose  = new QPushButton (tr ("Close"),  this);
    buttonDataSave         = new QPushButton (tr ("Save"),   this);
    buttonItemAdd          = new QPushButton (tr ("Add"),    this);
    buttonItemRemove       = new QPushButton (tr ("Remove"), this);
    buttonDataSourceClose->setDisabled (true);
    buttonDataSave->setDisabled        (true);
    buttonItemAdd->setDisabled         (true);
    buttonItemRemove->setDisabled      (true);

    editDataSource         = new QLineEdit (this);
}



void StorageManageWidget::createLayouts ()
{
    QHBoxLayout * layoutDataSource = new QHBoxLayout ();
    layoutDataSource->addWidget (new QLabel (tr ("Data source:"), this) );
    layoutDataSource->addWidget (editDataSource);
    layoutDataSource->addWidget (buttonDataSourceBrowse);
    QHBoxLayout * layoutActions = new QHBoxLayout ();
    layoutActions->addWidget (buttonItemAdd);
    layoutActions->addWidget (buttonItemRemove);
    layoutActions->addStretch ();
    layoutActions->addWidget (buttonDataSave);
    layoutActions->addWidget (buttonDataSourceOpen);
    layoutActions->addWidget (buttonDataSourceClose);
    QVBoxLayout * layoutControl = new QVBoxLayout ();
    layoutControl->addLayout (layoutDataSource);
    layoutControl->addLayout (layoutActions);

    QVBoxLayout * layoutTop = new QVBoxLayout ();
    layoutTop->addLayout (layoutControl);
    layoutTop->addWidget (tableCodes);
    layoutTop->addWidget (tableSequences);
    layoutTop->addWidget (tableReferences);
    this->setLayout (layoutTop);
}



void StorageManageWidget::createConnections ()
{
    connect (buttonDataSourceBrowse, SIGNAL (clicked () ), this, SLOT (onDataSourceBrowsing () ) );
    connect (buttonDataSourceOpen,   SIGNAL (clicked () ), this, SLOT (onDataSourceOpening  () ) );
    connect (buttonDataSourceClose,  SIGNAL (clicked () ), this, SLOT (onDataSourceClosing  () ) );
    connect (buttonDataSave,         SIGNAL (clicked () ), this, SLOT (onDataSourceSaving   () ) );
    connect (buttonItemAdd,          SIGNAL (clicked () ), this, SLOT (onItemAdding         () ) );
    connect (buttonItemRemove,       SIGNAL (clicked () ), this, SLOT (onItemRemoving       () ) );
    connect (tableCodes->selectionModel (), SIGNAL (selectionChanged (QItemSelection, QItemSelection) ), this, SLOT (onModelCodesSelectionChanged (QItemSelection, QItemSelection) ) );
    connect (qApp, SIGNAL (focusChanged (QWidget *, QWidget *) ), this, SLOT (onFocusChanged (QWidget *, QWidget *) ) );
    connect (modelCodes,      SIGNAL (itemChanged (QStandardItem *) ), this, SLOT (onModelCodesItemChanged      (QStandardItem *) ) );
    connect (modelSequences,  SIGNAL (itemChanged (QStandardItem *) ), this, SLOT (onModelSequencesItemChanged  (QStandardItem *) ) );
    connect (modelReferences, SIGNAL (itemChanged (QStandardItem *) ), this, SLOT (onModelReferencesItemChanged (QStandardItem *) ) );
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
        cellId->setData (code.attribute ("id").value (), Qt::DisplayRole);

        QStandardItem * cellLength = new QStandardItem ();
        cellLength->setTextAlignment (Qt::AlignCenter);
        cellLength->setData (code.attribute ("length").value (), Qt::DisplayRole);

        QStandardItem * cellMsl = new QStandardItem ();
        cellMsl->setTextAlignment (Qt::AlignCenter);
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

    buttonDataSourceOpen->setDisabled  (true);
    buttonDataSourceClose->setDisabled (false);
}



void StorageManageWidget::onDataSourceClosing ()
{
    delete xmlManager;
    xmlManager = nullptr;

    modelCodes->removeRows      (0, modelCodes->rowCount      () );
    modelSequences->removeRows  (0, modelSequences->rowCount  () );
    modelReferences->removeRows (0, modelReferences->rowCount () );

    buttonDataSourceOpen->setDisabled  (false);
    buttonDataSourceClose->setDisabled (true);
    buttonDataSave->setDisabled        (true);
}



void StorageManageWidget::onDataSourceSaving ()
{
    xmlManager->Clear ();

    for (int i = 0; i < modelCodes->rowCount (); ++i) {
        const std::string id     = modelCodes->item (i, columnNumberId    )->data (Qt::DisplayRole).toString ().toStdString ();
        const std::string length = modelCodes->item (i, columnNumberLength)->data (Qt::DisplayRole).toString ().toStdString ();
        const std::string maxpsl = modelCodes->item (i, columnNumberMsl   )->data (Qt::DisplayRole).toString ().toStdString ();
        xmlManager->InsertCode (id, std::stoi (length), std::stoi (maxpsl) );

        QModelIndex indexId = modelCodes->item (i, columnNumberId)->index ();
        for (int j = 0; j < modelCodes->itemFromIndex (indexId)->rowCount (); ++j) {
            switch (modelCodes->data (modelCodes->index (j, columnNumberId, indexId), DataTypeRole).toInt () ) {
                case DataTypeSequence:
                {
                    const std::string sequence {modelCodes->data (modelCodes->index (j, columnNumberId, indexId), Qt::DisplayRole).toString ().toStdString ()};
                    xmlManager->InsertCodeSequence (id, sequence);
                    break;
                }
                case DataTypeReference:
                {
                    const std::string article {modelCodes->data (modelCodes->index (j, columnNumberArticle, indexId), Qt::DisplayRole).toString ().toStdString ()};
                    const std::string author  {modelCodes->data (modelCodes->index (j, columnNumberAuthor,  indexId), Qt::DisplayRole).toString ().toStdString ()};
                    const std::string link    {modelCodes->data (modelCodes->index (j, columnNumberLink,    indexId), Qt::DisplayRole).toString ().toStdString ()};
                    xmlManager->InsertCodeReference (id, article, author, link);
                    break;
                }
            }
        }
    }
    
    xmlManager->Save ();

    buttonDataSave->setDisabled (true);
}



void StorageManageWidget::onModelCodesSelectionChanged (QItemSelection selectedItem, QItemSelection deselectedItem)
{
    if (deselectedItem.indexes ().size () ) {
        QModelIndex index = modelCodes->item (deselectedItem.indexes ().first ().row (), columnNumberId)->index ();

        modelCodes->itemFromIndex (index)->removeRows (0, modelCodes->itemFromIndex (index)->rowCount () );
        const int modelSequencesRowCount {modelSequences->rowCount ()};
        for (int i = 0; i < modelSequencesRowCount; ++i) {
            modelCodes->itemFromIndex (index)->appendRow (modelSequences->takeRow (0) );
        }
        const int modelReferencesRowCount {modelReferences->rowCount ()};
        for (int i = 0; i < modelReferencesRowCount; ++i) {
            modelCodes->itemFromIndex (index)->appendRow (modelReferences->takeRow (0) );
        }
    }

    if (selectedItem.indexes ().size () ) {
        QModelIndex index = modelCodes->item (selectedItem.indexes ().first ().row (), columnNumberId)->index ();

        modelSequences->removeRows  (0, modelSequences->rowCount  () );
        modelReferences->removeRows (0, modelReferences->rowCount () );

        for (int i = 0; i < modelCodes->itemFromIndex (index)->rowCount (); ++i) {
            switch (modelCodes->data (modelCodes->index (i, columnNumberId, index), DataTypeRole).toInt () ) {
                case DataTypeSequence:
                {
                    QStandardItem * cell = new QStandardItem ();
                    cell->setData (modelCodes->data (modelCodes->index (i, columnNumberId, index), Qt::DisplayRole), Qt::DisplayRole);
                    cell->setData (DataTypeSequence, DataTypeRole);
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
                    cellArticle->setData (DataTypeReference, DataTypeRole);
                    modelReferences->appendRow ({cellArticle, cellAuthor, cellLink});
                    break;
                }
            }
        }
    }
}



void StorageManageWidget::onModelCodesItemChanged (QStandardItem * item)
{
    buttonDataSave->setDisabled (false);
}



void StorageManageWidget::onModelSequencesItemChanged (QStandardItem * item)
{
    buttonDataSave->setDisabled (false);
}



void StorageManageWidget::onModelReferencesItemChanged (QStandardItem * item)
{
    buttonDataSave->setDisabled (false);
}



void StorageManageWidget::onFocusChanged (QWidget *, QWidget * widgetFocused)
{
    if (widgetFocused == tableCodes || widgetFocused == tableSequences || widgetFocused == tableReferences) {
        buttonItemAdd->setDisabled    (false);
        buttonItemRemove->setDisabled (false);
        tableFocused = widgetFocused;
    }
    else if (widgetFocused == buttonItemAdd || widgetFocused == buttonItemRemove) {
    }
    else {
        buttonItemAdd->setDisabled    (true);
        buttonItemRemove->setDisabled (true);
        widgetFocused = nullptr;
    }
}



void StorageManageWidget::onItemAdding ()
{
    if (tableFocused == tableCodes) {
        QStandardItem * cellId     = new QStandardItem ();
        QStandardItem * cellLength = new QStandardItem ();
        QStandardItem * cellMsl    = new QStandardItem ();
        cellId->setTextAlignment     (Qt::AlignLeft | Qt::AlignVCenter);
        cellLength->setTextAlignment (Qt::AlignCenter);
        cellMsl->setTextAlignment    (Qt::AlignCenter);
        modelCodes->appendRow ({cellId, cellLength, cellMsl});
    }
    else if (tableFocused == tableSequences) {
        QStandardItem * cellSequence = new QStandardItem ();
        cellSequence->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
        cellSequence->setData (DataTypeSequence, DataTypeRole);
        modelSequences->appendRow ({cellSequence});
    }
    else if (tableFocused == tableReferences) {
        QStandardItem * cellArticle = new QStandardItem ();
        QStandardItem * cellAuthor  = new QStandardItem ();
        QStandardItem * cellLink    = new QStandardItem ();
        cellArticle->setTextAlignment (Qt::AlignLeft | Qt::AlignVCenter);
        cellAuthor->setTextAlignment  (Qt::AlignCenter);
        cellLink->setTextAlignment    (Qt::AlignCenter);
        cellArticle->setData (DataTypeReference, DataTypeRole);
        modelReferences->appendRow ({cellArticle, cellAuthor, cellLink});
    }

    buttonDataSave->setDisabled (false);
}



void StorageManageWidget::onItemRemoving ()
{
    if (tableFocused == tableCodes) {
        while (tableCodes->selectionModel ()->hasSelection () ) {
            modelCodes->removeRow (tableCodes->selectionModel ()->selectedIndexes ().first ().row () );
        }
    }
    else if (tableFocused == tableSequences) {
        while (tableSequences->selectionModel ()->hasSelection () ) {
            modelSequences->removeRow (tableSequences->selectionModel ()->selectedIndexes ().first ().row () );
        }
    }
    else if (tableFocused == tableReferences) {
        while (tableReferences->selectionModel ()->hasSelection () ) {
            modelReferences->removeRow (tableReferences->selectionModel ()->selectedIndexes ().first ().row () );
        }
    }

    buttonDataSave->setDisabled (false);
}