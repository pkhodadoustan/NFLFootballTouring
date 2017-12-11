#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H

#include <QMainWindow>
#include<QSqlQuery>
#include "database.h"
#include <QDebug>
#include <QSortFilterProxyModel>
#include<vector>

/**
 * class information
 */
namespace Ui {
class InformationWindow;
}

/**
 * @brief The InformationWindow class
 * outputs general information for each class
 */
class InformationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformationWindow(QWidget *parent = 0);
    ~InformationWindow();
private slots:
    /**
     * @brief on_comboBox_activated
     * @param index
     * output iformation for teams
     */
    void on_comboBox_activated(int index);

    /**
     * @brief on_comboBox_2_activated
     * @param index
     * get the team index
     */
    void on_comboBox_2_activated(int index);

private:
    /**
     * @brief ui
     * ui ptr
     */
    Ui::InformationWindow *ui;

    /**
     * @brief makeTeamNameCombobox
     * creates team name combo
     */
    void makeTeamNameCombobox();

    /**
     * @brief displayAmericanConfTeams
     * displaysamerican conf teams
     */
    void displayAmericanConfTeams();
    /**
     * @brief displayNationalConfTeams
     * dispalys national conf teams
     */
    void displayNationalConfTeams();

    /**
     * @brief displayOpenRoof
     * displays open roof teams
     */
    void displayOpenRoof();

    /**
     * @brief displayAllTeams
     * displays all teams
     */
    void displayAllTeams();
};

#endif // INFORMATIONWINDOW_H
