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

void MainWindow::richTextToText()
{
    // Will use this to help convert and seephrase edit items to text in order to fill DB correctly
}

void MainWindow::createUI()
{
    ui->menubar->addMenu("Menu bar");
    ui->statusbar->showMessage("status bar");
}

void MainWindow::onSignupRequest()
{

}

void MainWindow::onLoginRequest()
{
    this->show();
}

void MainWindow::on_saveButton_clicked()
{
     int userId = mDb->getUserId(mUsername);
     mUserId = userId;

     EntryData data;
     data.username = ui->usernameLineEdit->text();
     data.site = ui->websiteLineEdit->text();
     data.pass = ui->passwordLineEdit->text();
     data.pin = ui->pinLineEdit->text();
     data.seed = ui->seedEdit->toPlainText();

    if(!mDb->entryExists(userId, data.site))
    {
        int passInfoDbId = mDb->addEntry(userId, data);

        QList<int> allPassIds = mDb->listAllPassIdsForUserId(userId);

        EntryData dataBack = mDb->entryDataForPassId(passInfoDbId);

        ui->usernameLineEdit->setText(dataBack.username + "Back");
        ui->websiteLineEdit->setText(dataBack.site + "Back");
        ui->passwordLineEdit->setText(dataBack.pass + "Back");
        ui->pinLineEdit->setText(dataBack.pin + "Back");
        ui->seedEdit->setPlainText(dataBack.seed + "Back");
    }
    else
    {
        data.passId = mDb->getPassId(userId, data.site);
        qDebug() << "Current Password ID:" << data.passId;
        mDb->editEntry(data.passId, data);
    }

}
