#ifndef TRIPFROMCOLISEUM_H
#define TRIPFROMCOLISEUM_H

#include <QDialog>
#include <vector>
#include <QDialog>
#include "graph.h"
#include "database.h"

/**
 *trip from coliseum
 */
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
    /**
     * @brief on_pushButton_clicked
     */
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    /**
     * @brief on_pushButton_DFS_clicked
     * DFS
     */
    void on_pushButton_DFS_clicked();

    /**
     * @brief on_pushButton_BFS_clicked
     * BFS
     */
    void on_pushButton_BFS_clicked();

private:
    /**
     * @brief ui
     * ui ptr
     */
    Ui::TripFromColiseum *ui;

    /**
     * @brief db
     * creates DB link
     */
    Database* db;
    /**
     * @brief fillGraphWithDistances
     * @return
     * fills the graph with DB distances
     */
    vector<QString> fillGraphWithDistances();
    /**
     * @brief stadiumGraph
     * stadium graphs
     */
    Graph stadiumGraph;

    /**
     * @brief convertStadiumNameToIndex
     * @return
     * converts stadium name to index
     */
    int convertStadiumNameToIndex(QString);

    /**
     * @brief addDistances
     * adds distances t graph
     */
    void addDistances();
    /**
     * @brief stads
     * adds stadiums
     */
    QStringList stads;

    /**
     * @brief selectedStadiums
     * list of selected staiums
     */
    std::vector<vNode> selectedStadiums;
    /**
     * @brief startingPoint
     * starting points
     */
    vNode startingPoint;


};

#endif // TRIPFROMCOLISEUM_H
