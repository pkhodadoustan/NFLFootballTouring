#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "mainwindow.h"
#include "database.h"


AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Admin Portal");

    // center the screen
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x,y);

    refreshList();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_backButton_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

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

void AdminWindow::on_addSouvButton_clicked()
{
    AddNewSouvenir* addSouv = new AddNewSouvenir;
    this->close();
    addSouv->show();
}
