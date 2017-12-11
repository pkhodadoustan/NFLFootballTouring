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

    void on_pushButton_2_clicked();

    void on_pushButton_DFS_clicked();

    void on_pushButton_BFS_clicked();

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


};

#endif // TRIPFROMCOLISEUM_H
