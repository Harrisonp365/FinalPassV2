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

    //Edit Password storage entries below
    void editEntry(int passId, SiteData& data);
    int addEntry(int userId, SiteData& data);
    bool siteDataEntryExist(const QString& site);
    QList<SiteData> listAllSiteInfoForUserId(int userId) const;

    int getUserId(const QString& username) const;

    QList<int> listAllPassIds() const;
    QList<int> listAllPassIdsForUserId(int userId) const;
    SiteData siteDataForPassId(int passId) const;
    bool entryExists(int userId, const QString site);

private:
    bool createUsersTable();
    bool createPassTable();
    bool deleteEntry(int userId, SiteData& data);
    void listAllEntries() const;



private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
