#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
//Below are incls that might change
#include <QMessageBox>
#include <QDebug>

#include "IOClass.h"
#include "LoginDialog.h"
#include "SignupDialog.h"



SignupDialog::SignupDialog(QWidget *parent) :
    QDialog{parent},
    mIO{new IOClass}
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
        QLabel *Header = new QLabel(tr("Please enter your password below and confirm"), this);
        mPasswordEdit = new QLineEdit(this);
        mPasswordConfirm = new QLineEdit(this);
        QPushButton *checkPassBtn = new QPushButton(tr("&Signup..."), this);

        signupWindowLayout->addWidget(Header, Qt::AlignHCenter);
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
        QMessageBox::information(this, "Signup", "Signup successful");
        passwordToStorage();
        return true;
        //send
    }
    else
    {
        QMessageBox::warning(this, "Signup", "Passwords do not match");
        return false;
        //need to work out how to keep dialog here
    }
}

void SignupDialog::passwordToStorage()
{
    mIO->writePassword(mPasswordConfirm->text());
}
