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

    //Signin/Login functions below
    bool addUser(const QString& username, const QString& password);
    bool removeUser(const QString& username, const QString& password);
    bool userExists(const QString& username, const QString& password);
    bool usernameExists(const QString& username);
    void listAllUsers() const;
    bool removeAllUsers();
    //Password storage functions below
    //id INTEGER PRIMARY KEY, userId INTEGER, app TEXT, username TEXT, email TEXT, password TEXT, pin INTEGER, seed TEXT
    bool createPassTable();
    int getUserId(const QString& username, const QString& password);
    bool addPassword(const int& userId, const QString& site, const QString& username, const QString& email, const QString& password, const int& pin, const QString& seed);
    bool deleteEntry(const int& userId, const  QString& site);
    void listAllPasswords() const ;
    bool entryExists(const int& userId, const QString& site);

private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
