#include "tripfromcoliseum.h"
#include "ui_tripfromcoliseum.h"
#include "mainwindow.h"

TripFromColiseum::TripFromColiseum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TripFromColiseum)
{
    ui->setupUi(this);
    db = Database::getInstance();     //Db instance
    stadiumGraph = fillGraphWithDistances();
    addDistances();
    stadiumGraph.printGraph();
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



/**
 * @brief TripFromColiseum::fillGraphWithDistances
 * @return
 */
vector<QString> TripFromColiseum::fillGraphWithDistances() {
    stads =  db->getAllStadiumNames(); //gets and holds all stadiumNames
    std::vector<QString> lis;
    for (int i =0; i < stads.size(); i++)
    {
        lis.push_back(stads.at(i));
    }


    return  lis;
}

/**
 * @brief TripFromColiseum::convertStadiumNameToIndex
 * @param stad
 * @return
 */
int TripFromColiseum::convertStadiumNameToIndex(QString stad) {
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
 * @brief TripFromColiseum::addDistances
 */
void TripFromColiseum::addDistances() {
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


void TripFromColiseum::on_pushButton_2_clicked()
{
    int totalDist = 0;
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    //! setting up selected stadiums table
    QStringList headerTitles;
    headerTitles<<"begining"<<"end"<<"distance";
    ui->tableWidget->setColumnCount(headerTitles.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerTitles);
    vector<edge> mstEdges = stadiumGraph.mst(10);
    for(unsigned int i = 0; i<mstEdges.size(); i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(mstEdges[i].begining));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(mstEdges[i].end));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(mstEdges[i].distance)));
        totalDist+= mstEdges[i].distance;
    }
    ui->label_totalDist->setText(QString::number(totalDist));
}

void TripFromColiseum::on_pushButton_DFS_clicked()
{
    //find the starting point in the graph
    for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
    {
        if(stadiumGraph.getAdjacencyList()[i][0].nodeName == "Hard Rock Stadium")
            startingPoint = stadiumGraph.getAdjacencyList()[i][0];
    }

    //perform DFS based on starting point
    stadiumGraph.DFS(startingPoint.key);
    vector<edge> edges = stadiumGraph.getDiscoveryEdges();

    //display the result in table
    int totalDist = 0;
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    //! setting up selected stadiums table
    QStringList headerTitles;
    headerTitles<<"begining"<<"end"<<"distance";
    ui->tableWidget->setColumnCount(headerTitles.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerTitles);
    for(unsigned int i = 0; i<edges.size(); i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(edges[i].begining));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(edges[i].end));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(edges[i].distance)));
        totalDist+= edges[i].distance;
    }
    ui->label_totalDist->setText(QString::number(totalDist));
}

void TripFromColiseum::on_pushButton_BFS_clicked()
{
    //find the starting point in the graph
    for(unsigned int i = 0; i<stadiumGraph.getAdjacencyList().size(); i++)
    {
        if(stadiumGraph.getAdjacencyList()[i][0].nodeName == "Lambeau Field")
            startingPoint = stadiumGraph.getAdjacencyList()[i][0];
    }
    //perform BFS based on starting point
    stadiumGraph.BFS(startingPoint.key);
    vector<edge> edges = stadiumGraph.getDiscoveryEdges();

    //display the result in table
    int totalDist = 0;
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    //! setting up selected stadiums table
    QStringList headerTitles;
    headerTitles<<"begining"<<"end"<<"distance";
    ui->tableWidget->setColumnCount(headerTitles.size());
    ui->tableWidget->setHorizontalHeaderLabels(headerTitles);
    for(unsigned int i = 0; i<edges.size(); i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(edges[i].begining));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(edges[i].end));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(edges[i].distance)));
        totalDist+= edges[i].distance;
    }
    ui->label_totalDist->setText(QString::number(totalDist));
}
