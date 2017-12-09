#ifndef CUSTOMTRIP_H
#define CUSTOMTRIP_H
#include <vector>
#include <QDialog>
#include "graph.h"
#include "database.h"
namespace Ui {
class CustomTrip;
}

class CustomTrip : public QDialog
{
    Q_OBJECT

public:
    explicit CustomTrip(QWidget *parent = 0);
    ~CustomTrip();

private slots:
    void on_pushButton_back_clicked();

    void on_comboBox_stadiums_currentIndexChanged(int index);

    void on_comboBox_teams_currentIndexChanged(int index);

    void on_comboBox_souvenirs_currentIndexChanged(int index);

    void on_pushButton_add_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_clicked();

    void on_comboBox_AllStadiums_currentIndexChanged(int index);

    void on_pushButton_findPath_clicked();

    void on_comboBox_StartingPoint_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_resetTrip_clicked();

private:
    Ui::CustomTrip *ui;
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

#endif // CUSTOMTRIP_H
