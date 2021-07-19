#include "DbManager.h"
#include "DbUtils.h"

DbManager* DbManager::instance()
{
    static DbManager* obj = nullptr; // new DbManager(DB::databasePath);
    if (!obj)
        obj = new DbManager(DB::databasePath);
    return obj;
}

DbManager::DbManager(const QString& path)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(path);

    if(!mDb.open())
        qDebug() << "Database connection failed";
    else
        qDebug() << "Database connected";
}

DbManager::~DbManager()
{
    if (mDb.isOpen())
        mDb.close();
}

bool DbManager::isOpen() const
{
    return mDb.isOpen();
}

void DbManager::initTables()
{
    createUsersTable();
    createPassTable();
}

bool DbManager::createUsersTable()
{
    QSqlQuery query(mDb);
    query.prepare("CREATE TABLE users(id INTEGER PRIMARY KEY, username TEXT, password TEXT);");

    bool result = query.exec();
    if(!result)
        qDebug() << "Could not create Users table, may already exist";

    return result;
}

bool DbManager::addUser(const QString &username, const QString &password)
{
    QSqlQuery query(mDb);
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    bool result = query.exec();
    if(!result)
        qDebug() << "addUser() error: " << query.lastError();

    return result;
}

bool DbManager::removeUser(const QString &username, const QString &password)
{
    bool result = false;

    if(userExists(username, password))
    {
        QSqlQuery query(mDb);
        query.prepare("DELETE FROM users WHERE username = (:username) AND password = (:password)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        result = query.exec();

        if(!result)
            qDebug() << "removeUser() error" << query.lastError();
    }
    return result;
}

bool DbManager::userExists(const QString &username, const QString &password)
{
    QSqlQuery query(mDb);
    query.prepare("SELECT username, password FROM users WHERE username = (:username) AND password = (:password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    bool result = false;
    if (query.exec())
    {
       if (query.next())
          result = true;// it exists
        else
           qDebug() << "User not in DB";
    }
    return result;
}

bool DbManager::userNameExists(const QString &username)
{
    return (getUserId(username) >= 1);
}

void DbManager::listAllUsers() const
{
    qDebug() << "Usernames from DB: ";
    QSqlQuery query(mDb);
    query.prepare("SELECT * FROM users");
    int userId = query.record().indexOf("username");
    while(query.next())
    {
        QString user = query.value(userId).toString();
        qDebug() << "=> " << user;
    }
}

bool DbManager::removeAllUsers()
{
    QSqlQuery removeQuery(mDb);
    removeQuery.prepare("DELETE FROM users");

    bool result = removeQuery.exec();
    if (!result)
        qDebug() << "remove all users failed: " << removeQuery.lastError();

    return result;
}

int DbManager::getUserId(const QString &username) const
{
    QSqlQuery query(mDb);
    query.prepare("SELECT id FROM users WHERE username = (:username)");
    query.bindValue(":username", username);

    int id = -1;
    if(query.exec())
    {
        if(query.next())
        {
            id = query.value(0).toInt();
        }
    }
    return id;
}

//Password storage functions

bool DbManager::createPassTable()
{
    QSqlQuery query(mDb);
    query.prepare("CREATE TABLE PasswordEntries(id INTEGER PRIMARY KEY, userId INTEGER, site TEXT, username TEXT, password TEXT, pin INTEGER, seed TEXT);");

    bool result = query.exec();
    if(!result)
        qDebug() << "Could not create PasswordEntries table, may already exist";
    return result;
}

int DbManager::addEntry(int userId, EntryData& data)
{
    QSqlQuery query(mDb);
    query.prepare("INSERT INTO PasswordEntries (ID, userId, site, username, password, pin, seed) VALUES (:ID, :userId, :site, :username, :password, :pin, :seed)");
    query.bindValue("ID", data.id);
    query.bindValue(":userId", userId);
    query.bindValue(":site", data.site);
    query.bindValue(":username", data.username);
    query.bindValue(":password", data.pass);
    query.bindValue(":pin", data.pin);
    query.bindValue(":seed", data.seed);

    bool result = query.exec();
    int id = -1;
    if (result) {
        id = query.lastInsertId().toInt();
        qDebug() << "pass id on add is:" << id;
    }
    else {
        qDebug() << "addPassword() error: " << query.lastError();
    }

    return id;
}

bool DbManager::editEntry(int passId, EntryData &data)
{
    QSqlQuery query(mDb);
    query.prepare("UPDATE PasswordEntries (site, username, password, pin, seed) VALUES (:site, :username, :password, :pin, :seed) WHERE id = :passId");
    query.bindValue(":site", data.site);
    query.bindValue(":username", data.username);
    query.bindValue(":password", data.pass);
    query.bindValue(":pin", data.pin);
    query.bindValue(":seed", data.seed);
    query.bindValue(":passId", passId);

    bool result = query.exec();
    if(!result)
        qDebug() << "Could not edit entry";
    else
        qDebug() << "Entry updated";
    return result;
}

QList<int> DbManager::listAllPassIdsForUserId(int userId) const
{
    QSqlQuery query(mDb);
    query.prepare("SELECT id FROM PasswordEntries WHERE userId = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << query.lastQuery() << query.lastError().text();
        return {};
    }

    QList<int> list;
    while (query.next())
    {
        list << query.value(0).toInt();
    }
    qDebug() << "list from sql query: " << list;
    return list;
}

EntryData DbManager::entryDataForPassId(int passId) const
{
    qDebug() << "entryDataForPassId called";
    QSqlQuery query(mDb);
    query.prepare("SELECT site, username, password, pin, seed FROM PasswordEntries WHERE id = :passId");
    query.bindValue(":passId", passId);

    if (!query.exec())
        return {};

    EntryData data;
    while (query.next())
    {
        data.site = query.value(0).toString();
        data.username = query.value(1).toString();
        data.pass = query.value(2).toString();
        data.pin = query.value(3).toString();
        data.seed = query.value(4).toString();
    }

    return data;
}

bool DbManager::deleteEntry(int userId, EntryData& data)
{
    bool result = false;

    if(entryExists(userId, data.site))
    {
        QSqlQuery query(mDb);
        query.prepare("DELETE FROM PasswordEntries WHERE userId = (:userId) AND site = (:site)");
        query.bindValue(":userId", userId);
        query.bindValue(":site", data.site);
        result = query.exec();

        if(!result)
            qDebug() << "deleteEntry() error" << query.lastError();
    }
    return result;
}

void DbManager::listAllEntries() const
{
    qDebug() << "users from password DB from DB: ";
    QSqlQuery query(mDb);
    query.prepare("SELECT * FROM PasswordEntries");
    int userId = query.record().indexOf("userId");
    while(query.next())
    {
        QString user = query.value(userId).toString();
        qDebug() << "=> " << user;
    }
}

bool DbManager::entryExists(int userId, const QString& site)
{
    QSqlQuery query(mDb);
    query.prepare("SELECT userId, site FROM PasswordEntries WHERE userId = (:userId) AND site = (:site)");
    query.bindValue(":userId", userId);
    query.bindValue(":site", site);

    bool result = false;
    if (query.exec())
    {
        if (query.next())
            result = true;
        else
            qDebug() << "Entry not in DB";
    }
    return result;
}

int DbManager::getPassId(int userId, const QString& site)
{
    QSqlQuery query(mDb);
    query.prepare("SELECT id FROM PasswordEntries WHERE userId = (:userId) AND site = (:site)");
    query.bindValue(":userId", userId);
    query.bindValue(":site", site);

    // Extract the PassId for userId and site
    int passId = -1;
    if (query.exec())
    {
        if (query.next())
        {
            passId = query.value(0).toInt();
            qDebug() << "PassId query value is:" << passId;
        }
    }
    return passId;
}
