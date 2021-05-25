#include "IOClass.h"
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
    QDialog{parent},
    mIO{new IOClass},
    mDb{DbManager(DB::databasePath)}
{
    createUI();
}

SignupDialog::~SignupDialog()
{
    delete this;
    delete mIO;
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

        connect(checkPassBtn, SIGNAL(clicked()), this, SLOT(confirmSignupPassword()));
        setLayout(signupWindowLayout);
}

bool SignupDialog::confirmSignupPassword()
{
    bool confirmed;
    confirmed = mIO->confirmPassword(mPasswordEdit->text(), mPasswordConfirm->text());

    if(confirmed)
    {
        QMessageBox::information(this, "Signup", "User added to DB");
        passwordToStorage();

    }
    else
    {
        QMessageBox::warning(this, "Signup", "Passwords do not match");
        //need to work out how to keep dialog here---TODO
    }
}

void SignupDialog::userToDb()
{
    QString username = mUserEdit->text();
    mDb.addUser(username);
}

void SignupDialog::passwordToStorage()
{
    QString password = mPasswordConfirm->text();
    mDb.addPassword(password);
}
