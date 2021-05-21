#ifndef DBMANGER_H
#define DBMANGER_H
#include <QString>
#include <QtSql>

class DbManger
{
public:
    DbManger(const QString& path);
private:
    QSqlDatabase mDb;
};

#endif // DBMANGER_H
