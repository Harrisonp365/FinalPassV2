#include "DbManager.h"

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

bool DbManager::addUser(const QString &username)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO users (username) VALUES (:username)");
    query.bindValue(":username", username);

    if(query.exec())
        success = true;
    else
        qDebug() << "addUser() error: " << query.lastError();

    return success;
}

bool DbManager::removeUser(const QString &username)
{
    bool success = false;

    if(userExists(username))
    {
        QSqlQuery query;
        query.prepare("DELETE FROM users WHERE username = (:username)");
        query.bindValue(":username", username);
        success = query.exec();

        if(!success)
            qDebug() << "removeUser() error" << query.lastError();
    }
    return success;
}

bool DbManager::userExists(const QString &username)
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


