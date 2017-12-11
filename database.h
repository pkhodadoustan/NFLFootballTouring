#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFile>
#include<vector>

/**
 * @brief The Database class
 * creates the link to the DB
 */
class Database : public QSqlDatabase
{
public:
    /**
     * @brief getInstance
     * @return
     * gets the db address
     */
    static Database* getInstance();

    /**
     * @brief initialDBPoputaion
     * fills DB with the inital information
     */
    void initialDBPoputaion();
    /**
     * @brief parseCSVFile
     * @return
     * parses CSV file
     */
    QStringList parseCSVFile(QString&);
    /**
     * @brief addNewTeam
     * adds a new team to the DB
     */
    void addNewTeam(QStringList);
    /**
     * @brief getListOfNationalConferenceTeams
     * @return
     * returns all natinal conferndce teams
     */
    QSqlQueryModel* getListOfNationalConferenceTeams();

    /**
     * @brief getListOfAmericanConferenceTeams
     * @return
     * returns all american confernece teams
     */
    QSqlQueryModel* getListOfAmericanConferenceTeams();
    /**
     * @brief getListOfOpenRoofStadiums
     * @return
     * returns list of open roof stadiums
     */
    QSqlQueryModel* getListOfOpenRoofStadiums();
    /**
     * @brief getAllStadiumByCapacity
     * @return
     * returns all stadiums by capacity
     */
    QSqlQueryModel* getAllStadiumByCapacity();
    /**
     * @brief getListOfAllTeams
     * @return
     * returns all teams
     */
    QSqlQueryModel* getListOfAllTeams();
    /**
     * @brief getSpecificTeamInfo
     * @param teamName
     * @return
     * get team information
     */
    QSqlQueryModel* getSpecificTeamInfo(QString teamName);

    /**
     * @brief getTotalNumberOfSeats
     * @return
     * returns total number of seats
     */
    int getTotalNumberOfSeats();

    /**
     * @brief getTeamNames
     * @return
     * returns all team names
     */
    std::vector<QString> getTeamNames();

    /**
     * @brief getListOfStarPLayers
     * @return
     * returns list of star placyers
     */
    QSqlQueryModel* getListOfStarPLayers();

    /**
     * @brief getListOfSurfaceTypes
     * @return
     * retuns surface types
     */
    QSqlQueryModel* getListOfSurfaceTypes();

    /**
     * @brief addStadiumDistancesFromFile
     * adds stadium distacnes
     */
    void addStadiumDistancesFromFile();

    /**
     * @brief addNewDistance
     * adds new distances
     */
    void addNewDistance(QStringList);

    /**
     * @brief addIntialSouvenirTables
     * initally fills the souv tables
     */
    void addIntialSouvenirTables();

    /**
     * @brief addSouvenir
     * @param team
     * @param price
     * @param souvenir
     * adds a new souv
     */
    void addSouvenir(QString team, QString price, QString souvenir);

    /**
     * @brief checkForSouvenir
     * @param team
     * @param price
     * @param souvenir
     * @return
     * checks to see if souv is in table
     */
    bool checkForSouvenir(QString team, QString price, QString souvenir);

    /**
     * @brief deleteSouv
     * @param Team
     * @param souv
     * deletes the souv
     */
    void deleteSouv(QString Team, QString souv);

    /**
     * @brief getAllStadiumNames
     * @return
     * retursn all stadium names
     */
    QStringList getAllStadiumNames() const;

    /**
     * @brief getAllDistances
     * @return
     * returns distacnes
     */
    QSqlQuery getAllDistances() const;

    /**
     * @brief addSouvenirTable
     * adds souv table
     */
    void addSouvenirTable(QString);

    /**
     * @brief getSouvenirsForTeam
     * @param team
     * @return
     * return souv for team
     */
    QStringList getSouvenirsForTeam(QString team) const;

    /**
     * @brief getSouvPrices
     * @param team
     * @return
     * get souv prices
     */
    QStringList getSouvPrices(QString team) const;

    /**
     * @brief getTeamInStadium
     * @param stadium
     * @return
     * get staium by team
     */
    QStringList getTeamInStadium(QString stadium) const;

private:

    /**
     * @brief Database
     * constructor
     */
    Database();

    /**
     * @brief instance
     * DB instance
     */
    static Database* instance;
    /**
     * @brief createQueryModel
     * @param queryCommand
     * @return
     */
    QSqlQueryModel* createQueryModel(QString queryCommand); //creates amodel depending on the query command passed to it
};

#endif // DATABASE_H
