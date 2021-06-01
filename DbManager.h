#ifndef DbManager_H
#define DbManager_H
#include <QObject>
#include <QString>
#include <QtSql>

class DbManager
{
public:
    static DbManager* instance();

    ~DbManager();
    bool isOpen() const;
    bool createTable();
    bool addUser(const QString& username, const QString &password);
    bool removeUser(const QString& username, const QString &password);
    bool userExists(const QString& username, const QString &password);
    bool usernameExists(const QString& username);
    void listAllUsers() const;
    bool removeAllUsers();

private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
