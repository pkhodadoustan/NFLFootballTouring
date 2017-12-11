#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlQuery>
#include <QTimer>
#include"informationwindow.h"
#include "logindialog.h"

/**
 *main window
 */
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * allows to user to select various differnet options
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief on_pushButton_Info_clicked
     * opens info window
     */
    void on_pushButton_Info_clicked();

    /**
     * @brief on_pushButton_4_clicked
     */
    void on_pushButton_4_clicked();

    /**
     * @brief on_pushButton_customTrip_2_clicked
     * custom trp
     */
    void on_pushButton_customTrip_2_clicked();

    /**
     * @brief on_pushButton_customTrip_clicked
     * trip from colusium
     */
    void on_pushButton_customTrip_clicked();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
