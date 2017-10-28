#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFile>
#include<vector>

class Database : public QSqlDatabase
{
public:
    static Database* getInstance();
    void initialDBPoputaion();
    QStringList parseCSVFile(QString&);
    void addNewTeam(QStringList);
    QSqlQueryModel* getListOfNationalConferenceTeams();
    QSqlQueryModel* getListOfAmericanConferenceTeams();
    QSqlQueryModel* getListOfOpenRoofStadiums();
    QSqlQueryModel* getListOfAllTeams();
    QSqlQueryModel* getSpecificTeamInfo(QString teamName);
    std::vector<QString> getTeamNames();
    QSqlQueryModel* getListOfStarPLayers();
    void addStadiumDistancesFromFile();
    void addNewDistance(QStringList);
private:
    Database();
    static Database* instance;
    QSqlQueryModel* createQueryModel(QString queryCommand); //creates amodel depending on the query command passed to it
};

#endif // DATABASE_H
