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
    void userToDb();
    void passwordToDb();
    bool checkPasswords();
    bool checkUsername();

private:
    QLineEdit* mUserEdit;
    QLineEdit* mPasswordEdit;
    QLineEdit* mPasswordConfirm;
    DbManager* mDb;
};

#endif // SIGNUPDIALOG_H
