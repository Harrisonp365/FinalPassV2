#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "DbManager.h"
#include "SignupDialog.h"
#include <QDialog>

class IOClass;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void signupRequest();
    void loginRequest();

private:
    void createUI();
    void createConnections();
    bool checkforUser();

private slots:
    void onSignupRequest();
    void onLoginRequest();

private:
    SignupDialog* mSignupDialog;
    QLineEdit* mUserNameLineEdit;
    QLineEdit* mPasswordLineEdit;
    DbManager mDb;
    IOClass*  mIO;
};

#endif // LOGINDIALOG_H
