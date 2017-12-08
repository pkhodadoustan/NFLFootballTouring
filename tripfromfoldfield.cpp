#include "tripfromfoldfield.h"
#include "ui_tripfromfoldfield.h"
#include "mainwindow.h"

TripFromFoldfield::TripFromFoldfield(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TripFromFoldfield)
{
    ui->setupUi(this);

    ui->comboBox_stadiums->insertItem(0," (Choose a Stadium) ");
    ui->comboBox_teams->insertItem(0," (Choose a Team) ");
    ui->comboBox_souvenirs->insertItem(0," (Choose a Souvenir) ");
}

TripFromFoldfield::~TripFromFoldfield()
{
    delete ui;
}

void TripFromFoldfield::on_pushButton_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}
