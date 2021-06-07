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

bool DbManager::createTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE users(id INTEGER PRIMARY KEY, username TEXT, password TEXT);");

    bool result = query.exec();
    if(!result)
        qDebug() << "Could not create user table, may already exist";

    return result;
}

bool DbManager::createPassTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE passStore(id INTEGER PRIMARY KEY, userId INTEGER, app TEXT, username TEXT, email TEXT, password TEXT, pin INTEGER, seed TEXT);");

    bool result = query.exec();
    if(!result)
        qDebug() << "Could not create table, may already exist";
    return result;
}

bool DbManager::addUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // Unsure if this is the correct way to do this

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
        QSqlQuery query;
        query.prepare("DELETE FROM users WHERE username = (:username) AND password = (:password)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        result = query.exec();

        if(!result)
            qDebug() << "removeUser() error" << query.lastError();
    }
    return result;
}

bool DbManager::usernameExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = (:username)");
    query.bindValue(":username", username);

    bool result = false;
    if (query.exec())
    {
       if (query.next())
            result = true;// it exists
    }
    return result;
}

bool DbManager::userExists(const QString &username, const QString &password)
{
    QSqlQuery query;
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
/*
int DbManager::getUserId(const QString &username, const QString &password)
{
    QSqlQuery query; // SELECT CURRENT_USER?
    query.prepare("SELECT CURRENT_USER FROM users ");


    if (query.exec())
    {
       if (query.next())
          id =
        else
           qDebug() << "User not in DB";
    }
    return id;
}
*/
void DbManager::listAllUsers() const
{
    qDebug() << "Usernames from DB: ";
    QSqlQuery query("SELECT * FROM users");
    int userId = query.record().indexOf("username");
    while(query.next())
    {
        QString user = query.value(userId).toString();
        qDebug() << "=> " << user;
    }
}

bool DbManager::removeAllUsers()
{
    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM users");

    bool result = removeQuery.exec();
    if (!result)
        qDebug() << "remove all users failed: " << removeQuery.lastError();

    return result;
}
