#include "tripfromcoliseum.h"
#include "ui_tripfromcoliseum.h"
#include "mainwindow.h"

TripFromColiseum::TripFromColiseum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TripFromColiseum)
{
    ui->setupUi(this);

    ui->comboBox_stadiums->insertItem(0," (Choose a Stadium) ");
    ui->comboBox_teams->insertItem(0," (Choose a Team) ");
    ui->comboBox_souvenirs->insertItem(0," (Choose a Souvenir) ");
}

TripFromColiseum::~TripFromColiseum()
{
    delete ui;
}

void TripFromColiseum::on_pushButton_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}
