#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QtSql>

class DbManger
{
public:
    DbManger(const QString& path);
    bool addUsername(const QString& username);
    bool addPassword(const QString& password);
    bool checkForUser(const QString& username);
private:
    QSqlDatabase mDb;
};

#endif // DBMANAGER_H
