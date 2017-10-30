#include "addnewsouvenir.h"
#include "ui_addnewsouvenir.h"

AddNewSouvenir::AddNewSouvenir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewSouvenir)
{
    Database* db = Database::getInstance();
    ui->setupUi(this);
    ui->TeamListCombo->setModel(db->getListOfAllTeams());
}

AddNewSouvenir::~AddNewSouvenir()
{
    delete ui;
}
