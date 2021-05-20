#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

#include "LoginDialog.h"
#include "IOClass.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog{parent},
    mIO{new IOClass}

{
   //setMinimumSize(500,500);
   createUI();
}

LoginDialog::~LoginDialog()
{
    delete this;
    delete mIO;
}

void LoginDialog::createUI()
{
    setWindowTitle(tr("Login"));
    QVBoxLayout *loginWindowLayout = new QVBoxLayout(this);
    QLabel *Header = new QLabel(tr("Welcome to FinalPass, please Login or Signup below"), this);
    mLoginLineEdit = new QLineEdit(this);
    QPushButton *signUpBtn = new QPushButton("&Signup...", this);

    loginWindowLayout->addWidget(Header, Qt::AlignHCenter);
    loginWindowLayout->addWidget(mLoginLineEdit, Qt::AlignHCenter);
    loginWindowLayout->addWidget(signUpBtn);

    connect(mLoginLineEdit, SIGNAL(returnPressed()), this, SLOT(onLoginRequest()));
    connect(signUpBtn, SIGNAL(clicked()), this, SLOT(onSignupRequest()));

    setLayout(loginWindowLayout);
}

bool LoginDialog::checkPassword()
{
   mIO->getPassword();
   return mIO->checkPassword(mLoginLineEdit->text());

}

void LoginDialog::onSignupRequest()
{
    hide();
    emit signupRequest();
    accept();
}

void LoginDialog::onLoginRequest()
{
    if(checkPassword())
    {
        hide();
        emit loginRequest();
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Password is incorrect");
        //exec();
        //work out how not to advance to either signup dialog on main window
    }

}
