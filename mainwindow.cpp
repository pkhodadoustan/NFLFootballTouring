#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QDebug>
#include <QSortFilterProxyModel>
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

void MainWindow::displayOpenRoof()
{
    ui->label->clear();
    ui->Table->setModel(Database::getInstance()->getListOfOpenRoofStadiums());
    QString input = QString("Open Roof Stadiums: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfOpenRoofStadiums());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);

}

void MainWindow::displayNationalConfTeams()
{
    ui->Table->setModel(Database::getInstance()->getListOfNationalConferenceTeams());
    QString input = QString("National Conference Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfNationalConferenceTeams());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);


}

void MainWindow::displayAllTeams()
{
    ui->Table->setModel(Database::getInstance()->getListOfAllTeams());
    QString input = QString("Number of Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    QSortFilterProxyModel *m = new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfAllTeams());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);
}

void MainWindow::displayAmericanConfTeams()
{
    ui->Table->setModel(Database::getInstance()->getListOfAmericanConferenceTeams());
    QString input = QString("American Conference Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    ui->Table->setSortingEnabled(true);
    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfAmericanConferenceTeams());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);
}

void MainWindow::makeTeamNameCombobox()
{
    //after index 0 and index 1 fill the comboBox with team names
    std::vector<QString> teamNames = Database::getInstance()->getTeamNames();
    for(unsigned int i =0; i<teamNames.size(); i++)
    {
        ui->comboBox->addItem(teamNames[i]);
    }
    ui->Table->setSortingEnabled(true);

}

void MainWindow::on_comboBox_activated(int index)
{
    if(index!=0)
    {
        if(index == 1)
        {
            ui->Table->setModel(Database::getInstance()->getListOfAllTeams());
            ui->Table->setSortingEnabled(true);
            QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
            m->setDynamicSortFilter(true);
            m->setSourceModel(Database::getInstance()->getListOfAllTeams());
            ui->Table->setModel(m);
            ui->Table->setSortingEnabled(true);
        }else{
        QString teamName = ui->comboBox->currentText();
        ui->Table->setModel(Database::getInstance()->getSpecificTeamInfo(teamName));
        }
    }
}

void MainWindow::on_comboBox_2_activated(int index)
{
    if(ui->comboBox_2->currentIndex() == 1)
    {
        displayAllTeams();
    }
    if(ui->comboBox_2->currentIndex() == 2)
    {
        displayAmericanConfTeams();
    }
    if(ui->comboBox_2->currentIndex() == 3)
    {
        displayNationalConfTeams();
    }
    if(ui->comboBox_2->currentIndex() == 4)
    {
        displayOpenRoof();
    }
    if(ui->comboBox_2->currentIndex() == 5)
    {
        ui->Table->setModel(Database::getInstance()->getListOfStarPLayers());
    }
}


