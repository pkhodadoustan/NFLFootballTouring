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
    QSqlQueryModel* getSpecificTeamInfo(QString teamName);
    std::vector<QString> getTeamNames();
    void addStadiumDistancesFromFile();
    void addNewDistance(QStringList);
private:
    Database();
    static Database* instance;
};

#endif // DATABASE_H
