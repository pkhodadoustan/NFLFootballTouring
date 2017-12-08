#include "customtrip.h"
#include "ui_customtrip.h"
#include "mainwindow.h"
#include "purchasesouvenirs.h"

CustomTrip::CustomTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomTrip)
{
    ui->setupUi(this);

    ui->comboBox_stadiums->insertItem(0," (Choose a Stadium) ");
    ui->comboBox_teams->insertItem(0," (Choose a Team) ");
    ui->comboBox_souvenirs->insertItem(0," (Choose a Souvenir) ");

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


void CustomTrip::on_comboBox_stadiums_currentIndexChanged(int index)
{
    ui->comboBox_teams->clear();
    ui->comboBox_souvenirs->clear();

}
