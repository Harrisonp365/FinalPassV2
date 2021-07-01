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

    void editEntry(int passId, const SiteData& data);
    int addEntry(int userId, const QString& site, const QString& username, const QString& password, int pin, const QString& seed);
    bool siteDataEntryExist(const QString& site);
    QList<SiteData> listAllSiteInfoForUserId(int userId) const;

    // Use SiteData.
    // bool addEntry(int userId, const QString& site, const QString& username, const QString& password, int pin, const QString& seed)

    int getUserId(const QString& username) const;

    QList<int> listAllPassIds() const;
    QList<int> listAllPassIdsForUserId(int userId) const;
    SiteData siteDataForPassId(int passId) const;

private:
    bool createUsersTable();
    bool createPassTable();
    bool deleteEntry(const int& userId, const  QString& site);
    void listAllEntries() const;

    bool entryExists(const int& userId, const QString& site);

private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
