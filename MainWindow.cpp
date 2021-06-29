#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginDialog.h"
#include "DbManager.h"
#include "DbUtils.h"
#include <QBoxLayout>
#include <QAction>
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
    {
        mDb->initTables();
    }
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
    ui->menubar->addMenu("Menu bar");
    ui->statusbar->showMessage("status bar");
    //ui-
    //ui->centralWidget->setLayoutDirection(LeftToRight);
    //ui->centralWidget->addAction()
}

void MainWindow::onSignupRequest()
{

}

void MainWindow::onLoginRequest()
{
    //mUserId = mDb->
    this->show();
}

void MainWindow::on_saveButton_clicked()
{

  //  const int& userId, const QString& site, const QString& username, const QString& password, const int& pin, const QString& seed
   int UserId = mDb->getUserId(mUsername);
   QString user = ui->usernameLineEdit->text();
   QString site = ui->websiteLineEdit->text();
   QString pass = ui->passwordLineEdit->text();
   QString seed = ui->seedEdit->toPlainText();

    mDb->addEntry(UserId, site, user, pass, 2, seed);
}

