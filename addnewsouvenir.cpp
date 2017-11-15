#include "addnewsouvenir.h"
#include "ui_addnewsouvenir.h"
#include <QDebug>
#include "database.h"
AddNewSouvenir::AddNewSouvenir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewSouvenir)
{
    Database* db = Database::getInstance();
    ui->setupUi(this);
    ui->TeamListCombo->setModel(db->getListOfAllTeams());
    ui->dollarLineEdit->setValidator(new QIntValidator(0, 100000, this));
}

AddNewSouvenir::~AddNewSouvenir()
{
    delete ui;
}

void AddNewSouvenir::on_addButton_clicked()
{
    Database* db = Database::getInstance();
    QString selectedTeam =ui->TeamListCombo->currentText();
    QString price;
    QString souv;
    ui->ErrorLabel->clear();
    if (!ui->SouvenirLineEdit->isModified() ||
            !ui->dollarLineEdit->isModified() ||
            !ui->CentLineEdit->isModified())
        ui->ErrorLabel->setText("Please fill out all fields");
    else {
           souv = ui->SouvenirLineEdit->text();
           price = ui->dollarLineEdit->text() + "." + ui->CentLineEdit->text();
           qDebug() << "select: " << selectedTeam;
           qDebug() << "souv: " << souv;
           qDebug() << "price: " << price;

           if (!db->checkForSouvenir(selectedTeam, price, souv))
           {
               db->addSouvenir(selectedTeam, price, souv);
               ui->ErrorLabel->setText("Souvenir has been added");
           } else {
               ui->ErrorLabel->setText("The Souvenir exists for this team");
           }

    }

}
