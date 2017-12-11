#include "informationwindow.h"
#include "ui_informationwindow.h"

/**
 * @brief InformationWindow::InformationWindow
 * @param parent
 */
InformationWindow::InformationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InformationWindow)
{
    ui->setupUi(this);
    makeTeamNameCombobox();
}

/**
 * @brief InformationWindow::~InformationWindow
 */
InformationWindow::~InformationWindow()
{
    delete ui;
}

/**
 * @brief InformationWindow::displayOpenRoof
 */
void InformationWindow::displayOpenRoof()
{
    ui->label->clear();
    ui->Table->setModel(Database::getInstance()->getListOfOpenRoofStadiums());
    QString input = QString("Open Roof Stadiums: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    ui->label_3->setText("");
    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfOpenRoofStadiums());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);

}

/**
 * @brief InformationWindow::displayNationalConfTeams
 */
void InformationWindow::displayNationalConfTeams()
{
    ui->Table->setModel(Database::getInstance()->getListOfNationalConferenceTeams());
    QString input = QString("National Conference Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    ui->label_3->setText("");
    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfNationalConferenceTeams());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);


}

/**
 * @brief InformationWindow::displayAllTeams
 */
void InformationWindow::displayAllTeams()
{
    ui->Table->setModel(Database::getInstance()->getListOfAllTeams());
    QString input = QString("Number of Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    QSortFilterProxyModel *m = new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfAllTeams());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);

    //QString input2 = QString("Total Number of Seats: %1").arg(Database::getInstance()->getTotalNumberOfSeats());
    //ui->label_3->setText(input2);
}

/**
 * @brief InformationWindow::displayAmericanConfTeams
 */
void InformationWindow::displayAmericanConfTeams()
{
    ui->Table->setModel(Database::getInstance()->getListOfAmericanConferenceTeams());
    QString input = QString("American Conference Teams: %1").arg(ui->Table->model()->rowCount());
    ui->label->setText(input);
    ui->label_3->setText("");
    ui->Table->setSortingEnabled(true);
    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(Database::getInstance()->getListOfAmericanConferenceTeams());
    ui->Table->setModel(m);
    ui->Table->setSortingEnabled(true);
}

/**
 * @brief InformationWindow::makeTeamNameCombobox
 */
void InformationWindow::makeTeamNameCombobox()
{
    //after index 0 and index 1 fill the comboBox with team names
    std::vector<QString> teamNames = Database::getInstance()->getTeamNames();
    for(unsigned int i =0; i<teamNames.size(); i++)
    {
        ui->comboBox->addItem(teamNames[i]);
    }
    ui->Table->setSortingEnabled(true);

}

/**
 * @brief InformationWindow::on_comboBox_activated
 * @param index
 */
void InformationWindow::on_comboBox_activated(int index)
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

/**
 * @brief InformationWindow::on_comboBox_2_activated
 * @param index
 */
void InformationWindow::on_comboBox_2_activated(int index)
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
    if(ui->comboBox_2->currentIndex() == 6)
    {
        ui->Table->setModel(Database::getInstance()->getListOfSurfaceTypes());
    }
    if(ui->comboBox_2->currentIndex() == 7)
    {
        ui->Table->setModel(Database::getInstance()->getAllStadiumByCapacity());
        QString input2 = QString("Total Number of Seats: %1").arg(Database::getInstance()->getTotalNumberOfSeats());
        ui->label_3->setText(input2);
    }
}
