#ifndef DbManager_H
#define DbManager_H
#include <QObject>
#include <QString>
#include <QtSql>

class DbManager
{
public:
    static DbManager* instance();
    DbManager(const QString& path);
    ~DbManager();
    bool isOpen() const;
    bool createTable();
    bool addUser(const QString& username, const QString &password);
    bool removeUser(const QString& username, const QString &password);
    bool userExists(const QString& username, const QString &password);
    void listAllUsers() const;
    bool removeAllUsers();

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
