#include "customtrip.h"
#include "ui_customtrip.h"
#include "mainwindow.h"
#include "purchasesouvenirs.h"
#include "database.h"

/**
 * @brief CustomTrip::CustomTrip
 * @param parent
 * sets up te Ui so that a user can create a custom trip.
 */
CustomTrip::CustomTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomTrip)
{
    ui->setupUi(this);

    db = Database::getInstance();     //Db instance
    stadiumGraph = fillGraphWithDistances();
   addDistances();
   stadiumGraph.printGraph();

   //! setting up combo box for list of stadiums
   ui->comboBox_AllStadiums->addItem("-- Select a Stadium from the List --");
   for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
   {
       //making the comboBox based on the stadiums in the graph
       ui->comboBox_AllStadiums->addItem(stadiumGraph.getAdjacencyList()[i][0].nodeName);
   }

   //! setting up combo box for LA Destinations
   ui->comboBox_LADest->addItem("-- Select a Stadium --");
   for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
   {
       if(stadiumGraph.getAdjacencyList()[i][0].nodeName != "Los Angeles Memorial Coliseum")
       {
            //making the comboBox based on the stadiums in the graph
            ui->comboBox_LADest->addItem(stadiumGraph.getAdjacencyList()[i][0].nodeName);
       }
   }

   //! setting up combo box for starting point
   ui->comboBox_StartingPoint->addItem("-- Select a Starting point --");

   //! setting up selected stadiums table
   QStringList headerTitles;
   headerTitles<<"Stadiums";
   ui->tableWidget_selectedStadiums->setColumnCount(headerTitles.size());
   ui->tableWidget_selectedStadiums->setHorizontalHeaderLabels(headerTitles);

    ui->comboBox_souvenirs->hide();
    ui->comboBox_stadiums->hide();
    ui->comboBox_teams->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label->hide();
    ui->label_add->hide();
    ui->lineEdit_quantity->hide();
    ui->pushButton_add->hide();
    ui->pushButton_print->hide();
    ui->tableWidget_receipt->hide();
    ui->totalLabel->hide();

    total = 0;

    ui->lineEdit_quantity->setValidator(new QIntValidator(0, 100, this));

    ui->tableWidget_selectedStadiums->setRowCount(0);
}

/**
 * @brief CustomTrip::~CustomTrip
 */
CustomTrip::~CustomTrip()
{
    delete ui;
}

/**
 * @brief CustomTrip::on_pushButton_back_clicked
 * goes back to the main window
 */
void CustomTrip::on_pushButton_back_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

/**
 * @brief CustomTrip::on_comboBox_stadiums_currentIndexChanged
 * @param index
 * gets the teams of the current team selected in the comvbo box
 */
void CustomTrip::on_comboBox_stadiums_currentIndexChanged(int index)
{
    QStringList teams = db->getTeamInStadium(ui->comboBox_stadiums->currentText());

    ui->comboBox_teams->clear();
    ui->comboBox_teams->addItem(" (Choose a Team) ");

    if(index > 0) {
        //initializing comboBox_teams with tempTeams vector
        ui->comboBox_teams->addItems(teams);
    }
}

/**
 * @brief CustomTrip::on_comboBox_teams_currentIndexChanged
 * @param index
 * creates a list for the souvs and prices
 */
void CustomTrip::on_comboBox_teams_currentIndexChanged(int index)
{

    //! Gets the souvenir list for specific team
    QStringList souvs = db->getSouvenirsForTeam(ui->comboBox_teams->currentText());
    //! Gets the prices for the souvenirs
    QStringList prices = db->getSouvPrices(ui->comboBox_teams->currentText());

    ui->comboBox_souvenirs->clear();
    ui->comboBox_souvenirs->addItem(" (Choose a Souvenir) ");

    if(index > 0) {
        //! initializing comboBox_souvenirs with souvenirs to specific team vector
        ui->comboBox_souvenirs->addItems(souvs);
    }

    //! stores the souvenirs and prices into vectors
    for(int i = 0;i < souvs.length(); i++)
    {
        tempSouvenirs.push_back(souvs[i]);
        tmpPrice.push_back(prices[i].remove(QChar('$')).toDouble());
    }
}

/**
 * @brief CustomTrip::on_comboBox_souvenirs_currentIndexChanged
 * @param index
 * changessouv list
 */
void CustomTrip::on_comboBox_souvenirs_currentIndexChanged(int index)
{
    if(index > 0) {
        ui->pushButton_add->show();
        souvenirName.push_back(tempSouvenirs.at(index-1));
        souvenirPrice.push_back(tmpPrice.at(index-1));
    }
}

/**
 * @brief CustomTrip::on_pushButton_add_clicked
 */
void CustomTrip::on_pushButton_add_clicked()
{
        //if lineEdit is empty, Print error msg
        if(ui->lineEdit_quantity->text().isEmpty())
        {
            QMessageBox::information(this, tr("Error"), tr("Please enter a value"));

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
 * @brief CustomTrip::on_pushButton_print_clicked
 */
void CustomTrip::on_pushButton_print_clicked()
{
   // QMessageBox::information(this, tr("Cart Emptied"), tr("The cart is now empty\n"
                                                           //"Printing receipt..."));

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

        ui->totalLabel->setText("Total: $" + QString::number(total));

        //clear all the vectors after printing the receipt
        souvenirName.clear();
        souvenirPrice.clear();
        souvenirQuantity.clear();
        totalPrice.clear();
        total = 0;
}

/**
 * @brief CustomTrip::on_pushButton_clicked
 */
void CustomTrip::on_pushButton_clicked()
{
    if(ui->tableWidget_selectedStadiums->rowCount() == 0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Please Plan a trip"));
    }
    else
    {
        ui->tableWidget_receipt->clear();
        ui->comboBox_stadiums->clear();
        ui->comboBox_teams->clear();
        ui->comboBox_souvenirs->clear();
        ui->label_first->hide();
        ui->comboBox_souvenirs->show();
        ui->comboBox_stadiums->show();
        ui->comboBox_teams->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->show();
        ui->label->show();
        ui->lineEdit_quantity->show();
        ui->tableWidget_receipt->show();
        ui->totalLabel->show();

        // populate stadium combobox

        QStringList listOfStadiums;

        for(unsigned int i = 0; i < ui->tableWidget_selectedStadiums->rowCount(); i++)
        {
            listOfStadiums += ui->tableWidget_selectedStadiums->item(i,0)->text();
        }

        ui->comboBox_stadiums->addItem(" (Choose a Stadium) ");
        ui->comboBox_stadiums->addItems(listOfStadiums);
    }
}


/**
 * @brief CustomTrip::fillGraphWithDistances
 * @return
 */
vector<QString> CustomTrip::fillGraphWithDistances() {
    stads =  db->getAllStadiumNames(); //gets and holds all stadiumNames
    std::vector<QString> lis;
    for (int i =0; i < stads.size(); i++)
    {
        lis.push_back(stads.at(i));
    }


    return  lis;
}

/**
 * @brief CustomTrip::convertStadiumNameToIndex
 * @param stad
 * @return
 */
int CustomTrip::convertStadiumNameToIndex(QString stad) {
    int index = -1;
    for (int i = 0; i < stads.size(); i++)
    {
        if (stad == stads.at(i))
        {
            index = i;
            break;
        }
    }
    return index;
}

/**
 * @brief CustomTrip::addDistances
 */
void CustomTrip::addDistances() {
    QSqlQuery query = db->getAllDistances();
    if (query.exec())
    {
        qDebug() << "Query was exec";
        while (query.next())
        {
            stadiumGraph.addAdjacentNoDirect(convertStadiumNameToIndex(query.value(0).toString()),
                                             convertStadiumNameToIndex(query.value(1).toString()),
                                             query.value(2).toInt());
        }
    } else
        qDebug() << "Query was not exec";
}

/**
 * @brief CustomTrip::on_comboBox_AllStadiums_currentIndexChanged
 * @param index
 */
void CustomTrip::on_comboBox_AllStadiums_currentIndexChanged(int index)
{
    /*populating vector of selected Stadiums and table of selected stadiums*/
    if(index!=0)//index 0 is not a name of a stadium; it is a message
    {
        QString newName = ui->comboBox_AllStadiums->currentText();
        bool duplicated = false;

        //to avoid selecting a stadium twice
        //check for duplication
        for(unsigned int i =0; i<selectedStadiums.size(); i++)
        {
            if(selectedStadiums.at(i).nodeName==newName) //if name is reapeted then item is duplicated
            {
                ui->labelWarning->setText("Warning: You have already added this stadium.");
                duplicated=true;
                break;
            }
        }
        //if not duplicated
        if(!duplicated)
        {
            /*adding a new selected stadium to the vecter of selected nodes*/
            QString stadiumName = ui->comboBox_AllStadiums->currentText();
            //find a vNode in a graph with same name and add it to the selectedStadiums vector
            for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
            {
                if(stadiumName == stadiumGraph.getAdjacencyList()[i][0].nodeName)
                {
                    selectedStadiums.push_back(stadiumGraph.getAdjacencyList()[i][0]);
                }
            }

            //selectedStadiums.push_back(newStadium);

            //! adding the selected item to table of selected stadiums
            ui->tableWidget_selectedStadiums->insertRow(selectedStadiums.size()-1);
            ui->tableWidget_selectedStadiums->setItem(selectedStadiums.size()-1, 0, new QTableWidgetItem(newName));

            //! adding the selected item to list of stadiums in the cmbo box of starting point selection
            ui->comboBox_StartingPoint->addItem(newName);

            //! adding the selected item to list of stadiums in the cmbo box of selected stadiums for souvenirs
            //ui->comboBoxSelectedColleges->addItem(newName);
        }
    }
}

/**
 * @brief CustomTrip::on_comboBox_StartingPoint_currentIndexChanged
 * @param index
 * gets the starting points
 */
void CustomTrip::on_comboBox_StartingPoint_currentIndexChanged(int index)
{
    if(ui->comboBox_StartingPoint->currentIndex() != 0)
    {
        for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
        {
            if(ui->comboBox_StartingPoint->currentText() == stadiumGraph.getAdjacencyList()[i][0].nodeName)
            {
                startingPoint = stadiumGraph.getAdjacencyList()[i][0];
            }
        }
    }
}

//this function calls the graph method that finds the most efficient path
/**
 * @brief CustomTrip::on_pushButton_findPath_clicked
 * finds the most efficient path
 */
void CustomTrip::on_pushButton_findPath_clicked()
{
    int totalDist = 0;
    vector<vNode> visited;
    stadiumGraph.findEfficientPath(selectedStadiums, startingPoint, visited);

    ui->tableWidget_selectedStadiums->clear();
    ui->tableWidget_selectedStadiums->setRowCount(0);
    for(unsigned int i =0; i<visited.size(); i++)
    {
        //! adding the visited stadium to the table
        ui->tableWidget_selectedStadiums->insertRow(i);
        ui->tableWidget_selectedStadiums->setItem(i, 0, new QTableWidgetItem(visited[i].nodeName));

        //finding total distance of the path
        totalDist += visited[i].distance;
    }
    ui->label_totalDist->setText(QString::number(totalDist));
}

//trip from FordField to all stadiums
/**
 * @brief CustomTrip::on_pushButton_2_clicked
 * creates a trip from fordfield
 */
void CustomTrip::on_pushButton_2_clicked()
{
   vector<vNode> visited;
   int totalDist = 0;

    //fill the selected sadiums with all stadiums, and startingPoint
    selectedStadiums.clear();
    for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
    {
        selectedStadiums.push_back(stadiumGraph.getAdjacencyList()[i][0]);
        if(stadiumGraph.getAdjacencyList()[i][0].nodeName == "Ford Field")
            startingPoint = stadiumGraph.getAdjacencyList()[i][0];
        //qDebug()<<selectedStadiums[i].nodeName<<endl;
    }
    //qDebug()<<selectedStadiums.size()<<endl;

    //find path
    stadiumGraph.findEfficientPath(selectedStadiums, startingPoint, visited);

    //displaying the result in the table
    ui->tableWidget_selectedStadiums->clear();
    ui->tableWidget_selectedStadiums->setRowCount(0);
    for(unsigned int i =0; i<visited.size(); i++)
    {
        //qDebug()<<visited[i].nodeName<<endl;
        //! adding the visited stadium to the table
        ui->tableWidget_selectedStadiums->insertRow(i);
        ui->tableWidget_selectedStadiums->setItem(i, 0, new QTableWidgetItem(visited[i].nodeName));

        //finding total distance of the path
        totalDist += visited[i].distance;
    }
    //display total distance
    ui->label_totalDist->setText(QString::number(totalDist));
}

/**
 * @brief CustomTrip::on_pushButton_resetTrip_clicked
 * resets the trip
 */
void CustomTrip::on_pushButton_resetTrip_clicked()
{
    selectedStadiums.clear();
    ui->tableWidget_selectedStadiums->clear();
    ui->tableWidget_selectedStadiums->setRowCount(0);
    ui->comboBox_StartingPoint->clear();
    ui->comboBox_StartingPoint->addItem("-- Select a Starting point --");
    vNode resetNode;
    startingPoint = resetNode;
    ui->label_totalDist->setText("");
}

/**
 * @brief CustomTrip::on_pushButton_orderedTrip_clicked
 * creates an ordered trip
 */
void CustomTrip::on_pushButton_orderedTrip_clicked()
{

    int totalDist = 0;
    vector<vNode> visited;
    for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
    {
        if(ui->tableWidget_selectedStadiums->item(0,0)->text() == stadiumGraph.getAdjacencyList()[i][0].nodeName)
        {
            startingPoint = stadiumGraph.getAdjacencyList()[i][0];
            stadiumGraph.orderSpecifiedPath(selectedStadiums, startingPoint, visited);
        }
    }
    for(unsigned int i =0; i<visited.size(); i++)
    {
        //finding total distance of the path
        totalDist += visited[i].distance;
    }
    ui->label_totalDist->setText(QString::number(totalDist));
}

/**
 * @brief CustomTrip::on_comboBox_LADest_currentIndexChanged
 * @param index
 * selects LA destination
 */
void CustomTrip::on_comboBox_LADest_currentIndexChanged(int index)
{
    int row = 2;
    ui->tableWidget_selectedStadiums->setRowCount(row);
    ui->tableWidget_selectedStadiums->clear();
    if(ui->comboBox_LADest->currentIndex()!=0)
    {
        //finding LA in the nodes of the graph
        for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
        {
            if(stadiumGraph.getAdjacencyList()[i][0].nodeName == "Los Angeles Memorial Coliseum")
            {
                selectedStadiums.push_back(stadiumGraph.getAdjacencyList()[i][0]);
                ui->tableWidget_selectedStadiums->setItem(0, 0, new QTableWidgetItem("Los Angeles Memorial Coliseum"));
                startingPoint = stadiumGraph.getAdjacencyList()[i][0];
            }
        }

        //calling Dijkstra from LA
        vector<vNode> destinations = stadiumGraph.dijkstra(startingPoint.key);

        //finding the destination that user has selected
        vNode userDest;
        for(unsigned int i = 0; i<destinations.size(); i++)
        {
            if(destinations[i].nodeName == ui->comboBox_LADest->currentText())
            {
                userDest = destinations[i];
                break;
            }

        }
        ui->label_totalDist_2->setText(QString::number(userDest.distance)+" miles");
    }

    /*adding a new selected stadium to the vecter of selected nodes*/
    QString stadiumName = ui->comboBox_LADest->currentText();
    //find a vNode in a graph with same name and add it to the selectedStadiums vector
    for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
    {
        if(stadiumName == stadiumGraph.getAdjacencyList()[i][0].nodeName)
        {
            selectedStadiums.push_back(stadiumGraph.getAdjacencyList()[i][0]);
        }
    }

    //selectedStadiums.push_back(newStadium);

    //! adding the selected item to table of selected stadiums
    ui->tableWidget_selectedStadiums->setItem(1, 0, new QTableWidgetItem(stadiumName));

    //! adding the selected item to list of stadiums in the cmbo box of starting point selection
    ui->comboBox_StartingPoint->addItem(stadiumName);
}
