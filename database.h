#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFile>

class Database : public QSqlDatabase
{
public:
    static Database* getInstance();
    void initialDBPoputaion();
    QStringList parseCSVFile(QString&);
    void addNewTeam(QStringList);
    QSqlQueryModel* getListOfNationalConferenceTeams();
    QSqlQueryModel* getListOfOpenRoofStadiums();
    void importDistancesFromFile();
private:
    Database();
    static Database* instance;
};

#endif // DATABASE_H
