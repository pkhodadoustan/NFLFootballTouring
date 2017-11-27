#include "customtrip.h"
#include "ui_customtrip.h"
#include "mainwindow.h"
#include "purchasesouvenirs.h"

CustomTrip::CustomTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomTrip)
{
    ui->setupUi(this);

   // ui->table1->setModel(Database::getInstance()->getAllStadiumByCapacity());
   // QString input = QString("All Stadiums: %1").arg(ui->table1->model()->rowCount());
    //ui->label->setText(input);
    //ui->label_3->setText("");
   // QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
   // m->setDynamicSortFilter(true);
    //m->setSourceModel(Database::getInstance()->getAllStadiumByCapacity());
    //ui->table1->setModel(m);
    //ui->table1->setSortingEnabled(true);
}

CustomTrip::~CustomTrip()
{
    delete ui;
}

void CustomTrip::on_pushButton_back_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

void CustomTrip::on_pushButton_purchase_clicked()
{
    PurchaseSouvenirs* purchaseS = new PurchaseSouvenirs;
    purchaseS->show();
}
