#ifndef TRIPFROMCOLISEUM_H
#define TRIPFROMCOLISEUM_H

#include <QDialog>
#include <vector>
#include <QDialog>
#include "graph.h"
#include "database.h"

namespace Ui {
class TripFromColiseum;
}

class TripFromColiseum : public QDialog
{
    Q_OBJECT

public:
    explicit TripFromColiseum(QWidget *parent = 0);
    ~TripFromColiseum();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_stadiums_currentIndexChanged(int index);

    void on_comboBox_teams_currentIndexChanged(int index);

    void on_comboBox_souvenirs_currentIndexChanged(int index);

    void on_pushButton_add_clicked();

    void on_pushButton_print_clicked();


    void on_pushButton_start_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TripFromColiseum *ui;
    Database* db;
    vector<QString> fillGraphWithDistances();
    Graph stadiumGraph;
    int convertStadiumNameToIndex(QString);
    void addDistances();
    QStringList stads;
    std::vector<vNode> selectedStadiums;
    vNode startingPoint;

    QVector<QString> souvenirName;
    QVector<double>  souvenirPrice;
    QVector<int>  souvenirQuantity;
    QVector<double>  totalPrice;
    double total;

    //temporary vectors, they will be deleted when we could read from data base
    QVector<QString> tempStadiums;
    QVector<QString> tempTeams;
    QVector<QString> tempSouvenirs;
    QVector<double> tmpPrice;

};

#endif // TRIPFROMCOLISEUM_H
