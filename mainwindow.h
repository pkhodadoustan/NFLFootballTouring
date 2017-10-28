#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

private:
    Ui::MainWindow *ui;
    void makeTeamNameCombobox();
    void displayAmericanConfTeams();
    void displayNationalConfTeams();
    void displayOpenRoof();
    void displayAllTeams();

};

#endif // MAINWINDOW_H
