#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QDebug>
#include<vector>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    makeTeamNameCombobox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenRoofButton_clicked()
{
    ui->label->clear();
    ui->Table->setModel(Database::getInstance()->getListOfOpenRoofStadiums());
    QString input = QString("Open Roof Stadiums: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
}

void MainWindow::on_NationalConfTeamsButton_clicked()
{
    ui->Table->setModel(Database::getInstance()->getListOfNationalConferenceTeams());
    QString input = QString("National Conference Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
}

void MainWindow::on_AmericanConfTeamsButton_clicked()
{
    ui->Table->setModel(Database::getInstance()->getListOfAmericanConferenceTeams());
    QString input = QString("American Conference Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index!=0)
    {
        QString teamName = ui->comboBox->currentText();
        ui->Table->setModel(Database::getInstance()->getSpecificTeamInfo(teamName));
    }

}

void MainWindow::makeTeamNameCombobox()
{
    std::vector<QString> teamNames = Database::getInstance()->getTeamNames();
    for(unsigned int i =0; i<teamNames.size(); i++)
    {
        ui->comboBox->addItem(teamNames[i]);
    }
}
