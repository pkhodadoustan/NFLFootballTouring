#ifndef CUSTOMTRIP_H
#define CUSTOMTRIP_H
#include <vector>
#include <QDialog>
#include "graph.h"
#include "database.h"

/**
 *custom trip
 */
namespace Ui {
class CustomTrip;
}

/**
 * @brief The CustomTrip class
 * allows the user to create a custom stadium trip
 */
class CustomTrip : public QDialog
{
    Q_OBJECT

public:
    explicit CustomTrip(QWidget *parent = 0);
    ~CustomTrip();

private slots:
    /**
     * @brief on_pushButton_back_clicked
     * creates new trip
     */
    void on_pushButton_back_clicked();

    /**
     * @brief on_comboBox_stadiums_currentIndexChanged
     * @param index
     * select places start at
     */
    void on_comboBox_stadiums_currentIndexChanged(int index);

    /**
     * @brief on_comboBox_teams_currentIndexChanged
     * @param index
     * select places to go
     */
    void on_comboBox_teams_currentIndexChanged(int index);

    /**
     * @brief on_comboBox_souvenirs_currentIndexChanged
     * @param index
     * allow souv selection
     */
    void on_comboBox_souvenirs_currentIndexChanged(int index);

    /**
     * @brief on_pushButton_add_clicked
     * adds souvenir to list
     */
    void on_pushButton_add_clicked();

    /**
     * @brief on_pushButton_print_clicked
     * prints the items
     */
    void on_pushButton_print_clicked();

    /**
     * @brief on_pushButton_clicked
     * ends the transaction
     */
    void on_pushButton_clicked();

    /**
     * @brief on_comboBox_AllStadiums_currentIndexChanged
     * @param index
     * changes the stadiums
     */
    void on_comboBox_AllStadiums_currentIndexChanged(int index);

    /**
     * @brief on_pushButton_findPath_clicked
     * find the shortest paths
     */
    void on_pushButton_findPath_clicked();

    /**
     * @brief on_comboBox_StartingPoint_currentIndexChanged
     * @param index
     * select starting point
     */
    void on_comboBox_StartingPoint_currentIndexChanged(int index);

    /**
     * @brief on_pushButton_2_clicked
     * end trip
     */
    void on_pushButton_2_clicked();

    /**
     * @brief on_pushButton_resetTrip_clicked
     * reset the trip
     */
    void on_pushButton_resetTrip_clicked();

    /**
     * @brief on_pushButton_orderedTrip_clicked
     * order teh trip
     */
    void on_pushButton_orderedTrip_clicked();
    /**
     * @brief on_comboBox_LADest_currentIndexChanged
     * @param index
     * change the destination
     */

    void on_comboBox_LADest_currentIndexChanged(int index);

private:
    /**
     * @brief ui
     * ui ptr
     */
    Ui::CustomTrip *ui;
    /**
     * @brief db
     * link to DB
     */
    Database* db;

    /**
     * @brief fillGraphWithDistances
     * @return
     * fills the graph
     */
    vector<QString> fillGraphWithDistances();
    /**
     * @brief stadiumGraph
     * creates a new graph
     */
    Graph stadiumGraph;
    /**
     * @brief convertStadiumNameToIndex
     * @return
     * converts strign to stadium indeces
     */
    int convertStadiumNameToIndex(QString);

    /**
     * @brief addDistances
     * adds distances to grapoh
     */
    void addDistances();
    /**
     * @brief stads
     * holds stadum anmes
     */
    QStringList stads;
    /**
     * @brief selectedStadiums
     * holds selected stadium
     */
    std::vector<vNode> selectedStadiums;
    /**
     * @brief startingPoint
     * startung point for trip
     */
    vNode startingPoint;
    /**
     * @brief souvenirName
     * holds souvenirs
     */
    QVector<QString> souvenirName;

    /**
     * @brief souvenirPrice
     * holds the price to souvs
     */
    QVector<double>  souvenirPrice;

    /**
     * @brief souvenirQuantity
     * holds number to souvenirs
     */
    QVector<int>  souvenirQuantity;

    /**
     * @brief totalPrice
     * hodls the total price
     */
    QVector<double>  totalPrice;

    /**
     * @brief total
     * holds souv total
     */
    double total;

    /**
     * @brief subtotal
     * hods subtotal
     */
    double subtotal;

    //temporary vectors, they will be deleted when we could read from data base
    QVector<QString> tempStadiums;
    QVector<QString> tempTeams;
    QVector<QString> tempSouvenirs;
    QVector<double> tmpPrice;
};

#endif // CUSTOMTRIP_H
