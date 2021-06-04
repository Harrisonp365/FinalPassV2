#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H
#include "DbManager.h"
#include <QDialog>

class QLineEdit;

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = nullptr);
    ~SignupDialog();

private slots:
    void createUI();
    void confirmSignup();

private:
    bool userToDb(const QString& username, const QString& pass);
    void passwordToDb();
    bool checkPasswords(const QString& pass1, const QString& pass2);
    bool checkUsername(const QString& username);

private:
    QLineEdit* mUserEdit;
    QLineEdit* mPasswordEdit;
    QLineEdit* mPasswordConfirm;
    DbManager* mDb;
};

#endif // SIGNUPDIALOG_H
