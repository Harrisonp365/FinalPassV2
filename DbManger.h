#ifndef DBMANGER_H
#define DBMANGER_H
#include <QString>
#include <QtSql>

class DbManger
{
public:
    DbManger(const QString& path);
    bool addUsername(const QString& username);
    bool addPassword(const QString& password);
private:
    QSqlDatabase mDb;
};

#endif // DBMANGER_H
