#include "database.h"
#include <QDir>
#include <QSqlError>
#include <QDebug>

Database* Database::instance = nullptr;


/**
 * @brief Database::getInstance
 * This function returns an instance of Database.  IF one is not created,
 * one will be created
 * @return Database*
 */
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
 * This function will take in a line as a QString of  a CSV file and input each item
 * into a QStringList
 * @param string
 * @return QString list
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

/**
 * @brief Database::addNewTeam
 * @param newTeam
 * This function adds a new Team on the Database.  It takes in a QString list and
 * goes item by item and adds to DB
 */
void Database::addNewTeam(QStringList newTeam) {
    QSqlQuery query(*this);
    query.prepare("INSERT INTO Teams (Team_Name, Stadium_Name, Seating_Capacity, Location,"
                  "Conference, Surface_Type, Stadium_Roof_Type, Star_Player) VALUES"
                  "(:Team, :Stadium, :Seating, :Locations, :Conference, :Surface, :Stadium_Roof, :Star)");

    query.bindValue(":Team", newTeam.at(0));
    query.bindValue(":Stadium", newTeam.at(1));
    query.bindValue(":Seating", newTeam.at(2));
    query.bindValue(":Locations", newTeam.at(3));
    query.bindValue(":Conference", newTeam.at(4));
    query.bindValue(":Surface", newTeam.at(5));
    query.bindValue(":Stadium_Roof", newTeam.at(6));
    query.bindValue(":Star", newTeam.at(7));


    if (query.exec())
        qDebug() << "query was executed";
    else
        qDebug() << "Query was not executed";

}

/**
 * @brief Database::initialDBPoputaion
 * This function will initally poputlate the Database.  It will find the path of
 * the relevent CSV file and call parseCSV and addTeams.
 */
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

QSqlQueryModel* Database::createQueryModel(QString queryCommand)
{
    QSqlQueryModel *model = new QSqlQueryModel;
      model->setQuery(queryCommand);
      model->setHeaderData(0, Qt::Horizontal, "Team Name");
      model->setHeaderData(1, Qt::Horizontal, "Stadium Name");
      model->setHeaderData(1, Qt::Horizontal, "Seating Capacity");
      model->setHeaderData(1, Qt::Horizontal, "Location");
      model->setHeaderData(1, Qt::Horizontal, "Conference");
      model->setHeaderData(1, Qt::Horizontal, "Surface Type");
      model->setHeaderData(1, Qt::Horizontal, "Stadium Roof Type");
      model->setHeaderData(1, Qt::Horizontal, "Star Player");

    return model;
}

QSqlQueryModel* Database::getListOfNationalConferenceTeams() {

    return createQueryModel("SELECT * FROM Teams WHERE Conference == 'National Football Conference'");
}

QSqlQueryModel* Database::getListOfOpenRoofStadiums() {

    return createQueryModel("SELECT * FROM Teams WHERE Stadium_Roof_Type == 'Open'");
}

QSqlQueryModel* Database::getListOfAmericanConferenceTeams() {

    return createQueryModel("SELECT * FROM Teams WHERE Conference == 'American Football Conference'");
}

QSqlQueryModel* Database::getListOfAllTeams()
{
   return createQueryModel("SELECT * FROM Teams");
}

QSqlQueryModel* Database::getSpecificTeamInfo(QString teamName)
{
    QString command = "SELECT * FROM Teams WHERE Team_Name == '"+teamName+"'";
    return createQueryModel(command);
}

std::vector<QString> Database::getTeamNames()
{
    std::vector<QString> teamNames;
    QSqlQuery query;
    query.prepare("SELECT * FROM Teams");
    if(!query.exec())
        qDebug()<<"unable to execute query";
    while(query.next())
    {
        teamNames.push_back(query.value(0).toString());
    }
    return teamNames;
}

void Database::addNewDistance(QStringList toAdd) {
    QSqlQuery query(*this);
    query.prepare("INSERT INTO StadiumDistances (Beginning, Ending, Distance)"
                  "VALUES (:beg, :end, :dist)");

    query.bindValue(":beg", toAdd.at(0));
    query.bindValue(":end", toAdd.at(1));
    query.bindValue(":dist", toAdd.at(2));

    if(query.exec())
        qDebug() << "distance was added";
    else
        qDebug() << "Distance was not added";
}

void Database::addStadiumDistancesFromFile() {
    Database* db = Database::getInstance();
    QDir dir(QDir::currentPath());
    QString path;
    qDebug() << dir.absolutePath();

    while(dir.dirName() != "NFLFootballTouring") {
        dir.cdUp();
    }

    path = dir.absolutePath() + "/Dist/NFLDistancesCSV/Distances-Table 1.csv";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        qDebug() << file.errorString();
    else {
        qDebug() << "Input file okay";

        while(!file.atEnd())
        {
            QString line = QString(file.readLine());
            QStringList toAdd = db->parseCSVFile(line);
            db->addNewDistance(toAdd);
        }
    }
}
