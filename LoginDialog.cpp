#include "DbManager.h"
#include "LoginDialog.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog{parent}
   ,mDb{DbManager::instance()}

{
   //setMinimumSize(500,500);
   createUI();
}

LoginDialog::~LoginDialog()
{
}

QString LoginDialog::username() const
{
    return mUserNameLineEdit->text();
}

QString LoginDialog::password() const
{
    return mPasswordLineEdit->text();
}

void LoginDialog::createUI()
{
    setWindowTitle(tr("Login"));
    QVBoxLayout *loginWindowLayout = new QVBoxLayout(this);
    QLabel *Header = new QLabel(tr("Welcome to FinalPass, please Login or Signup below"), this);
    mUserNameLineEdit = new QLineEdit(this);
    mPasswordLineEdit = new QLineEdit(this);
    mPasswordLineEdit->setEchoMode(QLineEdit::Password);
    QPushButton *loginBtn = new QPushButton("&Login...", this);
    QPushButton *signUpBtn = new QPushButton("&Signup...", this);

    loginWindowLayout->addWidget(Header, Qt::AlignHCenter);
    loginWindowLayout->addWidget(mUserNameLineEdit, Qt::AlignCenter);
    loginWindowLayout->addWidget(mPasswordLineEdit, Qt::AlignHCenter);
    loginWindowLayout->addWidget(loginBtn, Qt::AlignLeft); // maybe group box these buttons to align next to one another
    loginWindowLayout->addWidget(signUpBtn, Qt::AlignRight);

    connect(mPasswordLineEdit, SIGNAL(returnPressed()), this, SLOT(onLoginRequest()));
    connect(loginBtn, SIGNAL(clicked()), this, SLOT(onLoginRequest()));
    connect(signUpBtn, SIGNAL(clicked()), this, SLOT(onSignupRequest()));

    setLayout(loginWindowLayout);
}

bool LoginDialog::checkforUser()
{
    bool result = false;
    QString username = mUserNameLineEdit->text();
    QString password = mPasswordLineEdit->text();
    qDebug() << username;
    qDebug() << password;
    if(mDb->userExists(username, password))
        result = true;

    return result;
}

void LoginDialog::onSignupRequest()
{
    mSignupDialog = new SignupDialog(this);
    int state = mSignupDialog->exec();

    if(state != QDialog::Accepted)
    {
        qDebug() << "m_signupDialog accepted";
    }
    else
    {
        qDebug() << "m_signupDialog rejected";
    }
       delete mSignupDialog;
       mSignupDialog = nullptr;

       accept();
}

void LoginDialog::onLoginRequest()
{  
    if(checkforUser())
        accept();
    else
        reject();
}
