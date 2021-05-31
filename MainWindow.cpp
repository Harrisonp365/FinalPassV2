#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginDialog.h"
#include "DbManager.h"
#include "DbUtils.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , mLoginDialog{nullptr}
    , mDb{DbManager::instance()}
{
    ui->setupUi(this);
    createUI();

    //Database set up
    if (mDb->isOpen())
        mDb->createTable();
    else
        qDebug() << "Database is not open!";  
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    if(!mLoginDialog)
        showLoginDialog();
}

void MainWindow::showLoginDialog()
{
    mUsername = QString();

    mLoginDialog = new LoginDialog(this);
    connect(mLoginDialog, &LoginDialog::loginRequest, this, &MainWindow::onLoginRequest);
    connect(mLoginDialog, &LoginDialog::signupRequest, this, &MainWindow::onSignupRequest);

    int state = mLoginDialog->exec();

    if (state == QDialog::Accepted)
    {
        mUsername = mLoginDialog->username();
        mPass = mLoginDialog->password();
    }
    else
    {
        qDebug() << "m_loginDialog rejected";
    }

    delete mLoginDialog;
    mLoginDialog = nullptr;
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

}

void MainWindow::onLoginRequest()
{
    this->show();
}
