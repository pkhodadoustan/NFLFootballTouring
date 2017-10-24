#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenRoofButton_clicked()
{
    ui->label->clear();
    ui->Table->setModel(Database::getInstance()->getListOfOpenRoofStadiums());
}

void MainWindow::on_NationalConfTeamsButton_clicked()
{
    ui->Table->setModel(Database::getInstance()->getListOfNationalConferenceTeams());
    QString input = QString("Open Roof Stadiums: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
}
