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
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE users(id INTEGER PRIMARY KEY, username TEXT, password TEXT);");

    if(!query.exec())
    {
        qDebug() << "Could not create table, may already exist";
        success = false;
    }
    return success;
}

bool DbManager::addUser(const QString &username, const QString &password)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // Unsure if this is the correct way to do this

    if(query.exec())
        success = true;
    else
        qDebug() << "addUser() error: " << query.lastError();

    return success;
}

bool DbManager::removeUser(const QString &username, const QString &password)
{
    bool success = false;

    if(userExists(username, password))
    {
        QSqlQuery query;
        query.prepare("DELETE FROM users WHERE username = (:username) AND password = (:password)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        success = query.exec();

        if(!success)
            qDebug() << "removeUser() error" << query.lastError();
    }
    return success;
}

bool DbManager::usernameExists(const QString &username)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = (:username)");
    query.bindValue(":username", username);

    if (query.exec())
       if (query.next())
       {
          success = true;// it exists
       }

    return success;
}

bool DbManager::userExists(const QString &username, const QString &password)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("SELECT username, password FROM users WHERE username = (:username) AND password = (:password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec())
       if (query.next())
       {
          success = true;// it exists
       }

    return success;
}

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
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM users");

    if (removeQuery.exec())
        success = true;
    else
        qDebug() << "remove all users failed: " << removeQuery.lastError();

    return success;
}
