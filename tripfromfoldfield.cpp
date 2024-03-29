#include "tripfromfoldfield.h"
#include "ui_tripfromfoldfield.h"
#include "mainwindow.h"

/**
 * @brief TripFromFoldfield::TripFromFoldfield
 * @param parent
 */
TripFromFoldfield::TripFromFoldfield(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TripFromFoldfield)
{
    ui->setupUi(this);

    ui->comboBox_souvenirs->hide();
    ui->comboBox_stadiums->hide();
    ui->comboBox_teams->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_add->hide();
    ui->lineEdit_quantity->hide();
    ui->pushButton_add->hide();
    ui->pushButton_print->hide();
    ui->tableWidget_receipt->hide();
    ui->tableWidget_total->hide();

    //----------------------------------------------------------------------------
    //temporary vectors,they will be deleted after reading data from database
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

    total = 0;        //stores the total cost

    //initializing comboBox_stadiums with tempStadiums vector
    ui->comboBox_stadiums->insertItem(0," (Choose a Stadium) ");
    for(int i=0; i<tempStadiums.length(); i++)
    {
        ui->comboBox_stadiums->addItem(tempStadiums.at(i));
    }
}

/**
 * @brief TripFromFoldfield::~TripFromFoldfield
 */
TripFromFoldfield::~TripFromFoldfield()
{
    delete ui;
}

/**
 * @brief TripFromFoldfield::on_pushButton_clicked
 */
void TripFromFoldfield::on_pushButton_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

/**
 * @brief TripFromFoldfield::on_comboBox_stadiums_currentIndexChanged
 * @param index
 */
void TripFromFoldfield::on_comboBox_stadiums_currentIndexChanged(int index)
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

/**
 * @brief TripFromFoldfield::on_comboBox_teams_currentIndexChanged
 * @param index
 */
void TripFromFoldfield::on_comboBox_teams_currentIndexChanged(int index)
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

/**
 * @brief TripFromFoldfield::on_comboBox_souvenirs_currentIndexChanged
 * @param index
 */
void TripFromFoldfield::on_comboBox_souvenirs_currentIndexChanged(int index)
{
    if(index > 0) {
        ui->pushButton_add->show();
        souvenirName.push_back(tempSouvenirs.at(index-1));
        souvenirPrice.push_back(tmpPrice.at(index-1));
    }
}

/**
 * @brief TripFromFoldfield::on_pushButton_add_clicked
 */
void TripFromFoldfield::on_pushButton_add_clicked()
{
       //if lineEdit is empty, push 1 to vector
        if(ui->lineEdit_quantity->text().isEmpty())
        {
            souvenirQuantity.push_back(1);
            ui->pushButton_print->show();
            ui->label_add->show();
            QTimer::singleShot(2000, ui->label_add, &QLabel::hide);

        }
        else
        {
            //if lineEdit is not empty, push what user entered into the vector
            souvenirQuantity.push_back((ui->lineEdit_quantity->text()).toInt());
            ui->pushButton_print->show();
            ui->label_add->show();
            QTimer::singleShot(2000, ui->label_add, &QLabel::hide);

        }
}

/**
 * @brief TripFromFoldfield::on_pushButton_print_clicked
 */
void TripFromFoldfield::on_pushButton_print_clicked()
{
    //calculate total price for each souvenir and store it in totalPrice
    for(int i=0; i<souvenirName.length(); i++) {
        totalPrice.push_back(souvenirQuantity.at(i) * souvenirPrice.at(i));
    }


       //set receipt table
       ui->tableWidget_receipt->setRowCount(0);

       ui->tableWidget_receipt->setColumnCount(3);
       ui->tableWidget_receipt->setHorizontalHeaderItem(0, new QTableWidgetItem("Souvenir"));
       ui->tableWidget_receipt->setHorizontalHeaderItem(1, new QTableWidgetItem("Quantity"));
       ui->tableWidget_receipt->setHorizontalHeaderItem(2, new QTableWidgetItem("Price"));


       for (int i = 0; i < souvenirName.size(); i++) {
           ui->tableWidget_receipt->insertRow(ui->tableWidget_receipt->rowCount());
           ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 0,
                                              new QTableWidgetItem(souvenirName.at(i)));
           ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 1,
                                              new QTableWidgetItem(QString::number(souvenirQuantity.at(i))));
           ui->tableWidget_receipt->setItem(ui->tableWidget_receipt->rowCount() - 1, 2,
                                              new QTableWidgetItem("$" + QString::number(totalPrice.at(i))));
           total = total + totalPrice.at(i);
       }

       //set total table
       ui->tableWidget_total->setRowCount(0);
       ui->tableWidget_total->setColumnCount(1);

       ui->tableWidget_total->setHorizontalHeaderItem(0, new QTableWidgetItem("TOTAL"));
       ui->tableWidget_total->insertRow(ui->tableWidget_total->rowCount());
       ui->tableWidget_total->setItem(ui->tableWidget_total->rowCount() - 1, 0,
                                          new QTableWidgetItem("$" + QString::number(total)));

       //clear all the vectors after printing the receipt
       souvenirName.clear();
       souvenirPrice.clear();
       souvenirQuantity.clear();
       totalPrice.clear();
}

/**
 * @brief TripFromFoldfield::on_pushButton_start_clicked
 */
void TripFromFoldfield::on_pushButton_start_clicked()
{
    ui->label_first->hide();
    ui->comboBox_souvenirs->show();
    ui->comboBox_stadiums->show();
    ui->comboBox_teams->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_6->show();
    ui->lineEdit_quantity->show();
    ui->tableWidget_receipt->show();
    ui->tableWidget_total->show();
}
