#ifndef DbManager_H
#define DbManager_H
#include <QObject>
#include <QString>
#include <QtSql>

struct EntryData
{
    EntryData()
        : id(-1) {}

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
    bool editEntry(int passId, EntryData& data);
    int addEntry(int userId, EntryData& data);
    bool EntryDataEntryExist(const QString& site);
    QList<EntryData> listAllSiteInfoForUserId(int userId) const;

    int getUserId(const QString& username) const;

    //QList<int> listAllPassIds() const;
    QList<int> listAllPassIdsForUserId(int userId) const;
    EntryData entryDataForPassId(int passId) const;
    bool entryExists(int userId, const QString& site);
    int getPassId(int userId, const QString& site);

private:
    bool createUsersTable();
    bool createPassTable();
    bool deleteEntry(int userId, EntryData& data);
    void listAllEntries() const;

private:
    DbManager(const QString& path);

private:
    QSqlDatabase mDb;
};

#endif // DbManager_H
