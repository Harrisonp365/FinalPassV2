#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QLabel>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createUI();
    hide();

    mLoginDialog = new LoginDialog(this);
    connect(mLoginDialog, &LoginDialog::loginRequest, this, &MainWindow::onLoginRequest);
    connect(mLoginDialog, &LoginDialog::signupRequest, this, &MainWindow::onSignupRequest);

    bool state = mLoginDialog->exec();

    if (state)
    {
        //QDialog::Accepted
        qDebug() << "m_loginDialog accepted";
        onLoginRequest();
    }
    else
    {
        //QDialog::Rejected
        qDebug() << "m_loginDialog rejected";

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI()
{
    //Create UI here dont use the form
    setWindowTitle(tr("Main Window"));
    //QVBoxLayout *mainWindowLayout = new QVBoxLayout(this);
    //QLabel *Header = new QLabel("How are you passwords looking today?", this);
    //mainWindowLayout->addWidget(Header, Qt::AlignCenter);

}

void MainWindow::onSignupRequest()
{
    qDebug() << "onSignupRequested HIT";
    //if(!mSignUpDialog)
        mSignupDialog = new SignupDialog(this);

    bool state = mSignupDialog->exec();

        if (state)
        {
           //QDialog::Accepted
           qDebug() << "m_signupDialog accepted";
        }
        else
        {
            //QDialog::Rejected
            qDebug() << "m_signupDialog rejected";
        }
}

void MainWindow::onLoginRequest()
{
    this->show();
}
