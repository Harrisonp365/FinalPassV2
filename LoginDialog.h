#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
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
    bool checkPassword();

private slots:
    void onSignupRequest();
    void onLoginRequest();

private:
    SignupDialog* mSignupDialog;
    QLineEdit* mUserNameLineEdit;
    QLineEdit* mLoginLineEdit;
    IOClass*  mIO;
};

#endif // LOGINDIALOG_H
