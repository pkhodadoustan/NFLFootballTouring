#include "tripfromcoliseum.h"
#include "ui_tripfromcoliseum.h"
#include "mainwindow.h"

TripFromColiseum::TripFromColiseum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TripFromColiseum)
{
    ui->setupUi(this);

    //----------------------------------------------------------------------------
    //tempprary vectors,they will be deleted ater reading from data base
    tempStadiums.push_back("stadium 1");
    tempStadiums.push_back("stadium 2");
    tempStadiums.push_back("stadium 3");
    tempStadiums.push_back("stadium 4");
    tempStadiums.push_back("stadium 5");

    tempTeams.push_back("team 1");
    tempTeams.push_back("team 2");
    tempTeams.push_back("team 3");
    tempTeams.push_back("team 4");

    tempSouvenirs.push_back("item 1");
    tempSouvenirs.push_back("item 2");
    tempSouvenirs.push_back("item 3");
    tempSouvenirs.push_back("item 4");

    tmpPrice.push_back(10.99);
    tmpPrice.push_back(20.99);
    tmpPrice.push_back(30.99);
    tmpPrice.push_back(40.99);

    //----------------------------------------------------------------------------

    ui->label_add->hide();

    ui->comboBox_stadiums->insertItem(0," (Choose a Stadium) ");
    for(int i=0; i<tempStadiums.length(); i++)
    {
        ui->comboBox_stadiums->addItem(tempStadiums.at(i));
    }

    total = 0;
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

void TripFromColiseum::on_comboBox_stadiums_currentIndexChanged(int index)
{
    ui->comboBox_teams->clear();
    ui->comboBox_souvenirs->clear();

    if(index > 0) {
        //initializing comboBox_teams with tempTeams vector
        ui->comboBox_teams->insertItem(0," (Choose a Team) ");
        for(int i=0; i<tempTeams.length(); i++)
        {
            ui->comboBox_teams->addItem(tempTeams.at(i));
        }
    }
}

void TripFromColiseum::on_comboBox_teams_currentIndexChanged(int index)
{
    ui->comboBox_souvenirs->clear();
    if(index > 0) {
        //initializing comboBox_souvenirs with tempSouvenirs vector
        ui->comboBox_souvenirs->insertItem(0," (Choose a Souvenir) ");
        for(int i=0; i<tempSouvenirs.length(); i++)
        {
            ui->comboBox_souvenirs->addItem(tempSouvenirs.at(i));
        }
    }
}


void TripFromColiseum::on_comboBox_souvenirs_currentIndexChanged(int index)
{
    if(index > 0) {
        souvenirName.push_back(tempSouvenirs.at(index-1));
        souvenirPrice.push_back(tmpPrice.at(index-1));
    }
}

void TripFromColiseum::on_pushButton_add_clicked()
{
    //if lineEdit is empty, push 1 to vector
        if(ui->lineEdit_quantity->text().isEmpty())
        {
            souvenirQuantity.push_back(1);
            ui->label_add->show();
           // QTimer::singleShot(2000, ui->label_add, &QLabel::hide);

        }
        else
        {
            //if lineEdit is not empty, push what user entered into the vector
            souvenirQuantity.push_back((ui->lineEdit_quantity->text()).toInt());
            ui->label_add->show();
           // QTimer::singleShot(2000, ui->label_add, &QLabel::hide);

        }
}

void TripFromColiseum::on_pushButton_print_clicked()
{

}
