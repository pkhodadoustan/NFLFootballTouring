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


/**
 * @brief Database::parseAndReturnCSVFile
 * @param string
 * @return
 */
QStringList Database::parseCSVFile(QString &string) {
    enum State {Normal, Quote} state = Normal;
    QStringList fields;
    QString value;

    for (int i = 0; i < string.size(); i++)
    {
        QChar current = string.at(i);

        // Normal state
        if (state == Normal)
        {
            // Comma
            if (current == ',')
            {
                // Save field
                fields.append(value);
                value.clear();
            }

            // Double-quote
            else if (current == '"')
                state = Quote;

            // Other character
            else
                value += current;
        }

        // In-quote state
        else if (state == Quote)
        {
            // Another double-quote
            if (current == '"')
            {
                if (i+1 < string.size())
                {
                    QChar next = string.at(i+1);

                    // A double double-quote?
                    if (next == '"')
                    {
                        value += '"';
                        i++;
                    }
                    else
                        state = Normal;
                }
            }

            // Other character
            else
                value += current;
        }
    }
    if (!value.isEmpty())
        fields.append(value);

    return fields;
}

Database::addNewTeam(QStringList newTeam) {
    QSqlQuery query(*this);
    query.prepare("INSERT INTO Teams (Stadium Name, Seating Capacity, Locations,"
                  "Conference, Surface Type, Stadium Roof Type, Star Player)");
    query.bindValue(":Stadium Name", newTeam.at(0));
    query.bindValue(":Seating Capacity", newTeam.at(1));
    query.bindValue(":Locations", newTeam.at(2));
    query.bindValue(":Conference", newTeam.at(3));
    query.bindValue(":Surface Type", newTeam.at(4));
    query.bindValue(":Stadium Roof Type", newTeam.at(5));
    query.bindValue(":Star Player", newTeam.at(6));

    if (query.exec())
        qDebug() << "query was executed";
    else
        qDebug() << "Query was not executed";

}

void Database::initialDBPoputaion() {
    Database* db = Database::getInstance();
    QDir dir(QDir::currentPath()); //gets current path
    QString current;//holds new path
    qDebug() << dir.absolutePath();


    while(dir.dirName() != "NFLFootballTouring") {
        dir.cdUp();
    }
    current = dir.absolutePath() + "/initialData/NFLCSV.csv";
       QFile file(current);

       if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
        } else {
           qDebug() << "Input File is open";

           while (!file.atEnd())
           {
               QString line = QString(file.readLine());
               QStringList toAdd = db->parseCSVFile(line);
               db->addNewTeam(toAdd);
           }
       }
}
