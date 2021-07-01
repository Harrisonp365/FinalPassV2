#ifndef DbManager_H
#define DbManager_H
#include <QObject>
#include <QString>
#include <QtSql>

struct SiteData
{
    int id;
    QString site;
    QString username;
    QString pass;
    QString pin;
    QString seed;
};

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
    //Password storages functions
    bool addEntry(const int& userId, const QString& site, const QString& username, const QString& password, const int& pin, const QString& seed);
    void editEntry(int passId, const SiteData& data);
    int getUserId(const QString& username) const;
    bool siteDataEntryExist(const QString& site);
    QList<SiteData> listAllSiteInfoForUserId(int userId) const;

    QList<int> listAllPassIds() const;
    QList<int> listAllPassIdsForUserId(int userId) const;
    SiteData siteDataForPassId(int passId) const;

private:

    bool createTable();
    bool createPassTable();
    bool deleteEntry(const int& userId, const  QString& site);
    void listAllEntries() const ;
    bool entryExists(const int& userId, const QString& site);

private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
