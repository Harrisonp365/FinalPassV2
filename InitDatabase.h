#ifndef INITDATABASE_H
#define INITDATABASE_H
#include <QtSql>

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if(!db.open())
        return db.lastError();

    return QSqlError();
}
#endif // INITDATABASE_H
