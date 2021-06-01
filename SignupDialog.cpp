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
        mPasswordEdit = new QLineEdit(this);
        mPasswordEdit->setEchoMode(QLineEdit::Password);
        mPasswordConfirm = new QLineEdit(this);
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
    if(checkPasswords() == true && checkUsername() == true)
    {
        userToDb();
        QMessageBox::information(this, "Signup", "User added to DB");
        //QDialog::Accepted;
    }
}

void SignupDialog::userToDb()
{
    QString username = mUserEdit->text();
    QString password = mPasswordConfirm->text();
    mDb->addUser(username, password);
}

bool SignupDialog::checkPasswords()
{
    bool success = false;
    const QString pass1 = mPasswordEdit->text();
    const QString pass2 = mPasswordConfirm->text();

    if(mPasswordEdit->text() == mPasswordConfirm->text())
    {
       if(!(pass1 == ""))
       {
            success = true;
            qDebug() << "passwords match";
       }
       else
            QMessageBox::warning(this, "Signup", "Please enter a valid password");
    }
    else
       QMessageBox::warning(this, "Signup", "Passwords do not match");

    return success;
}

bool SignupDialog::checkUsername()
{
    bool success = false;
    QString username = mUserEdit->text();

    if(!mDb->usernameExists(username))
    {
        success = true;
        qDebug() << "username is valid";
    }
    else if(username == "")
        QMessageBox::warning(this, "Signup", "Please enter a username");
    else
        QMessageBox::warning(this, "Signup", "Username already exists");

    return success;
}

