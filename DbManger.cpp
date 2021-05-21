#include "DbManger.h"

DbManger::DbManger(const QString& path)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(path);

    if(!mDb.open())
        qDebug() << "Database connection failed";
    else
        qDebug() << "Database connected";
}

bool DbManger::addUsername(const QString &username)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO userDb (username) VALUES (:username)");
    query.bindValue(":username", username);

    if(query.exec())
        success = true;
    else
        qDebug() << "add user error: " << query.lastError();

    return success;
}

bool DbManger::addPassword(const QString &password)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO userDb (password) VALUES (:password)");
    query.bindValue(":password", password);
    if(query.exec())
        success = true;
    else
        qDebug() << "add password error: " << query.lastError();
}


