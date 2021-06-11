#include "LoginDialog.h"
#include "SignupDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
//Below are incls that might change
#include <QMessageBox>
#include <QDebug>

SignupDialog::SignupDialog(QWidget *parent) :
    QDialog{parent}
   ,mDb{DbManager::instance()}
{
    createUI();
}

SignupDialog::~SignupDialog()
{
}

void SignupDialog::createUI()
{
        setWindowTitle("Signup");
        QVBoxLayout *signupWindowLayout = new QVBoxLayout(this);
        QLabel *Header = new QLabel(tr("Please enter your password and username below and confirm"), this);
        mUserEdit = new QLineEdit(this);
        mUserEdit->setPlaceholderText("Username");

        mPasswordEdit = new QLineEdit(this);
        mPasswordEdit->setPlaceholderText("Password");
        mPasswordEdit->setEchoMode(QLineEdit::Password);

        mPasswordConfirm = new QLineEdit(this);
        mPasswordConfirm->setPlaceholderText("Confirm Password");
        mPasswordConfirm->setEchoMode(QLineEdit::Password);
        QPushButton *checkPassBtn = new QPushButton(tr("&Signup..."), this);

        signupWindowLayout->addWidget(Header, Qt::AlignHCenter);
        signupWindowLayout->addWidget(mUserEdit, Qt::AlignCenter);
        signupWindowLayout->addWidget(mPasswordEdit, Qt::AlignHCenter);
        signupWindowLayout->addWidget(mPasswordConfirm, Qt::AlignHCenter);
        signupWindowLayout->addWidget(checkPassBtn, Qt::AlignHCenter);

        connect(checkPassBtn, SIGNAL(clicked()), this, SLOT(confirmSignup()));
        setLayout(signupWindowLayout);
}

void SignupDialog::confirmSignup()
{
    QString username = mUserEdit->text();
    const QString pass1 = mPasswordConfirm->text();
    const QString pass2 = mPasswordConfirm->text();
    if(checkPasswords(pass1, pass2) && checkUsername(username) && userToDb(username, pass1))
    {
        QMessageBox::information(this, "Signup", "User added to DB");
        accept();
    }
}

bool SignupDialog::userToDb(const QString& username, const QString& password)
{
    return mDb->addUser(username, password);
}

bool SignupDialog::checkPasswords(const QString& pass1, const QString& pass2)
{
    bool result = false;

    if(pass1 == pass2)
    {
       if(!(pass1 == ""))
            result = true;
       else
            QMessageBox::warning(this, "Signup", "Please enter a valid password");
    }
    else
       QMessageBox::warning(this, "Signup", "Passwords do not match");

    return result;
}

bool SignupDialog::checkUsername(const QString& username)
{
    bool result = false;

    if(!mDb->userNameExists(username))
        result = true;
    else if(username.trimmed().isEmpty())
        QMessageBox::warning(this, "Signup", "Please enter a username");
    else
        QMessageBox::warning(this, "Signup", "Username already exists");

    return result;
}
