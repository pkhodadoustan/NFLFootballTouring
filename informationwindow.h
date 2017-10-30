#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H

#include <QMainWindow>
#include<QSqlQuery>
#include "database.h"
#include <QDebug>
#include <QSortFilterProxyModel>
#include<vector>
namespace Ui {
class InformationWindow;
}

class InformationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformationWindow(QWidget *parent = 0);
    ~InformationWindow();
private slots:
    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

private:
    Ui::InformationWindow *ui;
    void makeTeamNameCombobox();
    void displayAmericanConfTeams();
    void displayNationalConfTeams();
    void displayOpenRoof();
    void displayAllTeams();
};

#endif // INFORMATIONWINDOW_H
