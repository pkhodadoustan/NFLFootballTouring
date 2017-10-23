#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>

class Database : public QSqlDatabase
{
public:
    static Database* getInstance();
private:
    Database();
    static Database* instance;
};

#endif // DATABASE_H
