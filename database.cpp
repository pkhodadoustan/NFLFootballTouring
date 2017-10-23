#include "database.h"
#include <QDir>
#include <QDebug>

Database* Database::instance = nullptr;


Database* Database::getInstance() {
    if (instance == nullptr)
        instance = new Database;

    return instance;
}

/**
 * @brief Database::Database
 * creates a connection to a SQLite database file.  Verfies that
 * it is open
 */
Database::Database(): QSqlDatabase(addDatabase("QSQLITE")) {
    QDir dir(QDir::currentPath()); //gets current path
    QString current;//holds new path
    qDebug() << dir.absolutePath();


    while(dir.dirName() != "NFLFootballTouring") {
        dir.cdUp();
    }

    //adds path to database
    current = dir.absolutePath() + "/DB/DataB.db";
    qDebug() << "Path is " + current;

    //sets database path
    setDatabaseName(current);
    QFileInfo existingDatabaseInfo(current);

    //outputs if path exists
    if (existingDatabaseInfo.exists())
    {
        qDebug() << "Database file is open\n";
        open();
    }
    else
        qDebug() << "Datebase file is not open\n";
}
