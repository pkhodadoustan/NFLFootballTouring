#ifndef TRIPFROMFOLDFIELD_H
#define TRIPFROMFOLDFIELD_H

#include <QDialog>

/**
 * trip from Fold field
 */
namespace Ui {
class TripFromFoldfield;
}

/**
 * @brief The TripFromFoldfield class
 * UI to foldfield trip
 */
class TripFromFoldfield : public QDialog
{
    Q_OBJECT

public:
    explicit TripFromFoldfield(QWidget *parent = 0);
    ~TripFromFoldfield();

private slots:
    /**
     * @brief on_pushButton_clicked
     */
    void on_pushButton_clicked();

    /**
     * @brief on_comboBox_stadiums_currentIndexChanged
     * @param index
     */
    void on_comboBox_stadiums_currentIndexChanged(int index);

    /**
     * @brief on_comboBox_teams_currentIndexChanged
     * @param index
     */
    void on_comboBox_teams_currentIndexChanged(int index);

    /**
     * @brief on_comboBox_souvenirs_currentIndexChanged
     * @param index
     */
    void on_comboBox_souvenirs_currentIndexChanged(int index);

    /**
     * @brief on_pushButton_add_clicked
     */
    void on_pushButton_add_clicked();

    /**
     * @brief on_pushButton_print_clicked
     */
    void on_pushButton_print_clicked();

    /**
     * @brief on_pushButton_start_clicked
     */
    void on_pushButton_start_clicked();

private:
    /**
     * @brief ui
     */
    Ui::TripFromFoldfield *ui;

    /**
     * @brief souvenirName
     */
    QVector<QString> souvenirName;

    /**
     * @brief souvenirPrice
     */
    QVector<double>  souvenirPrice;
    /**
     * @brief souvenirQuantity
     */
    QVector<int>  souvenirQuantity;
    /**
     * @brief totalPrice
     */
    QVector<double>  totalPrice;
    /**
     * @brief total
     */
    double total;

    //temporary vectors, they will be deleted when we could read from data base
    QVector<QString> tempStadiums;
    QVector<QString> tempTeams;
    QVector<QString> tempSouvenirs;
    QVector<double> tmpPrice;
};

#endif // TRIPFROMFOLDFIELD_H
