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
    void initTables();

    //Signin/Login functions below
    bool addUser(const QString& username, const QString& password);
    bool removeUser(const QString& username, const QString& password);
    bool userExists(const QString& username, const QString& password);
    bool userNameExists(const QString& username);
    void listAllUsers() const;
    bool removeAllUsers();

    int getUserId(const QString& username) const;

private:

    bool createTable();
    bool createPassTable();
    bool addEntry(const int& userId, const QString& site, const QString& username, const QString& password, const int& pin, const QString& seed);
    bool deleteEntry(const int& userId, const  QString& site);
    void listAllEntries() const ;
    bool entryExists(const int& userId, const QString& site);

private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
