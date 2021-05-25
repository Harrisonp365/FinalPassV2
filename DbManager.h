#ifndef DbManager_H
#define DbManager_H
#include <QObject>
#include <QString>
#include <QtSql>

class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();
    bool isOpen() const;
    bool createTable();
    bool addUser(const QString& username);
    bool addPassword(const QString& password);
    bool removeUser(const QString& username);
    bool userExists(const QString& username);
    void listAllUsers() const;
private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
