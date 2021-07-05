#ifndef DbManager_H
#define DbManager_H
#include <QObject>
#include <QString>
#include <QtSql>


struct SiteData
{
    int id;
    QString site = "ds";
    QString username= "ds";
    QString pass= "ds";
    QString pin= "ds";
    QString seed= "ds";
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
    int addEntry(int userId, SiteData& data);
    bool siteDataEntryExist(const QString& site);
    QList<SiteData> listAllSiteInfoForUserId(int userId) const;

    int getUserId(const QString& username) const;

    QList<int> listAllPassIds() const;
    QList<int> listAllPassIdsForUserId(int userId) const;
    SiteData siteDataForPassId(int passId) const;
    bool entryExists(int userId, const QString& site);

private:
    bool createUsersTable();
    bool createPassTable();
    bool deleteEntry(const int& userId, const  QString& site);
    void listAllEntries() const;



private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
