#ifndef TRIPFROMFOLDFIELD_H
#define TRIPFROMFOLDFIELD_H

#include <QDialog>

namespace Ui {
class TripFromFoldfield;
}

class TripFromFoldfield : public QDialog
{
    Q_OBJECT

public:
    explicit TripFromFoldfield(QWidget *parent = 0);
    ~TripFromFoldfield();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_stadiums_currentIndexChanged(int index);


    void on_comboBox_teams_currentIndexChanged(int index);

    void on_comboBox_souvenirs_currentIndexChanged(int index);

    void on_pushButton_add_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::TripFromFoldfield *ui;

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

#endif // TRIPFROMFOLDFIELD_H
