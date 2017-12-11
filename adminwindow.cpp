#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "mainwindow.h"
#include "database.h"
#include <QMenu>
#include "filebrowerdiag.h"
#include <QItemSelectionModel>

/**
 * @brief AdminWindow::AdminWindow
 * @param parent
 * constructor for the admin window.  this links withe DB and fills all the tables
 * with the information from the stadim
 */
AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{

    Database* db = Database::getInstance();

    ui->setupUi(this);

    this->setWindowTitle("Admin Portal");

    // center the screen
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x,y);

    ui->TeamCombBox->setModel(db->getListOfAllTeams());

    QString test = QString("%1_Souv").arg(ui->TeamCombBox->currentText()).replace(" ", "_");
    qDebug() << test;
    QSqlTableModel* test2 = new QSqlTableModel;
    test2->setTable(test);
    if(!test2->select())
        qDebug() << "NOPE";
    ui->SouvView->setModel(test2);
    ui->SouvView->horizontalHeader()->setStretchLastSection(true);
    ui->SouvView->resizeRowsToContents();
    ui->SouvView->verticalHeader()->setDefaultSectionSize(50);

    ui->SouvView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->SouvView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(on_SouvView_customContextMenuRequested(const QPoint &)));
    ui->SouvView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    refreshList();

}

/**
 * @brief AdminWindow::~AdminWindow
 */
AdminWindow::~AdminWindow()
{
    delete ui;
}

/**
 * @brief AdminWindow::on_backButton_clicked
 * back to main
 */
void AdminWindow::on_backButton_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

/**
 * @brief AdminWindow::refreshList
 * refreshs the tables so that all the information displayed is up to date with DB
 */
void AdminWindow::refreshList() {
    tableModel = new QSqlTableModel; //creates new table model

    //sets and checks tableModel
    tableModel->setTable("Teams");
    if(!tableModel->select())
        qDebug() << "Table not okay";

    //fills table table with elements from Souvenir Table in DB
    ui->Table->setModel(tableModel);
    ui->Table->horizontalHeader()->setStretchLastSection(true);
    ui->Table->resizeRowsToContents();
    ui->Table->verticalHeader()->setDefaultSectionSize(50);

    //sets resize Model for table
    ui->Table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->Table, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
    ui->Table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //allows first column to be read-only
    ui->Table->setItemDelegateForColumn(0, new NotEditableDelegate(ui->Table));

}

/**
 * @brief AdminWindow::on_addSouvButton_clicked
 * adds a souvenir
 */
void AdminWindow::on_addSouvButton_clicked()
{
    AddNewSouvenir* addSouv = new AddNewSouvenir;
    addSouv->show();
    admin = this;
}

/**
 * @brief AdminWindow::onCustomContextMenu
 * @param point
 * deletes the items
 */
void AdminWindow::onCustomContextMenu(const QPoint &point)
{
    //menu to delete item on right click
    QMenu contextMenu(tr("Context menu"), this);

    //if item is right clicked, option to delete item is offered
    QAction action1("Delete Selection", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(deleteSelection()));
    contextMenu.addAction(&action1);
    contextMenu.exec(ui->Table->mapToGlobal(point));

}

/**
 * called when the user clicks delete on an item.  Item only gets deleted
 * if an entire row is selected.  item is deleted from the table as well as
 * the database.  The table is then refreshed
 * @brief AdminWindow::deleteSelection
 */
void AdminWindow::deleteSelection() {
    QString college; //college name
    QString Souv; //souvenir type

    //gets the selected items from the selected row
    QItemSelectionModel *select = ui->Table->selectionModel();
    college = select->selectedRows(0).value(0).data().toString();
    Souv = select->selectedRows(1).value(0).data().toString();

    //deletes item from DB
    Database* db = Database::getInstance();
    //db->deleteSouvenir(college, Souv);

    //able is refreshed
    refreshList();
}

/**
 * @brief AdminWindow::on_TeamCombBox_currentIndexChanged
 * @param index
 * diplays the selected team souvenirs to the souvenir table
 */
void AdminWindow::on_TeamCombBox_currentIndexChanged(int index)
{
    QString test = QString("%1_Souv").arg(ui->TeamCombBox->currentText()).replace(" ", "_");
    qDebug() << test;
    QSqlTableModel* test2 = new QSqlTableModel;
    test2->setTable(test);
    if(!test2->select())
        qDebug() << "NOPE";
    ui->SouvView->setModel(test2);
    ui->SouvView->horizontalHeader()->setStretchLastSection(true);
    ui->SouvView->resizeRowsToContents();
    ui->SouvView->verticalHeader()->setDefaultSectionSize(50);
}

/**
 * @brief AdminWindow::on_addStadButton_clicked
 * creates new file browser to select stadium additions
 */
void AdminWindow::on_addStadButton_clicked()
{
    FileBrowerDiag* file = new FileBrowerDiag;
    file->show();
}

/**
 * @brief AdminWindow::refreshSouvList
 */
void AdminWindow::refreshSouvList() {
    QString test = QString("%1_Souv").arg(ui->TeamCombBox->currentText()).replace(" ", "_");
    qDebug() << test;
    QSqlTableModel* test2 = new QSqlTableModel;
    test2->setTable(test);
    if(!test2->select())
        qDebug() << "NOPE";
    ui->SouvView->setModel(test2);
    ui->SouvView->horizontalHeader()->setStretchLastSection(true);
    ui->SouvView->resizeRowsToContents();
    ui->SouvView->verticalHeader()->setDefaultSectionSize(50);

    ui->SouvView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->SouvView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(on_SouvView_customContextMenuRequested(const QPoint &)));
    ui->SouvView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    refreshList();
}

void AdminWindow::on_SouvView_customContextMenuRequested(const QPoint &pos)
{
    //menu to delete item on right click
    QMenu contextMenu(tr("Context menu"), this);

    //if item is right clicked, option to delete item is offered
    QAction action1("Delete Selection", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(deleteSouv()));
    contextMenu.addAction(&action1);
    contextMenu.exec(ui->SouvView->mapToGlobal(pos));
}

void AdminWindow::deleteSouv() {
    QString Souv; //souvenir type

    //gets the selected items from the selected row
    QItemSelectionModel* select = ui->SouvView->selectionModel();
    Souv = select->selectedRows(0).value(0).data().toString();

    Database* db = Database::getInstance();
    db->deleteSouv(QString(ui->TeamCombBox->currentText()).replace(" ", "_"), Souv);

    refreshSouvList();
}
