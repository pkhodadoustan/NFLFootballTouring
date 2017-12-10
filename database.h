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
    QSqlQueryModel* getAllStadiumByCapacity();
    QSqlQueryModel* getListOfAllTeams();
    QSqlQueryModel* getSpecificTeamInfo(QString teamName);
    int getTotalNumberOfSeats();
    std::vector<QString> getTeamNames();
    QSqlQueryModel* getListOfStarPLayers();
    QSqlQueryModel* getListOfSurfaceTypes();
    void addStadiumDistancesFromFile();
    void addNewDistance(QStringList);
    void addIntialSouvenirTables();
    void addSouvenir(QString team, QString price, QString souvenir);
    bool checkForSouvenir(QString team, QString price, QString souvenir);
    void deleteSouv(QString Team, QString souv);
    QStringList getAllStadiumNames() const;
    QSqlQuery getAllDistances() const;
    void addSouvenirTable(QString);
    QStringList getSouvenirsForTeam(QString team) const;
    QStringList getSouvPrices(QString team) const;
    QStringList getTeamInStadium(QString stadium) const;

private:
    Database();
    static Database* instance;
    QSqlQueryModel* createQueryModel(QString queryCommand); //creates amodel depending on the query command passed to it
};

#endif // DATABASE_H
