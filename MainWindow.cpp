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

QList<int> MainWindow::showAllPasswordEntries()
{
    mUserId = mDb->getUserId(mUsername);

    //int passInfoDbId = mDb->addEntry(mUserId, data);
    QList<int> passIdToDisplay = mDb->listAllPassIdsForUserId(mUserId);
    qDebug() << "All Password entries to be displayed:" << passIdToDisplay;

    //EntryData dataBack = mDb->entryDataForPassId(passInfoDbId);
    return passIdToDisplay;
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
    //showAllPasswordEntries();
}

void MainWindow::on_saveButton_clicked()
{
    //mUserId = mDb->getUserId(mUsername);
    showAllPasswordEntries();
    /*


     EntryData data;
     data.username = ui->usernameLineEdit->text();
     data.site = ui->websiteLineEdit->text();
     data.pass = ui->passwordLineEdit->text();
     data.pin = ui->pinLineEdit->text();
     data.seed = ui->seedEdit->toPlainText();

    if(!mDb->entryExists(mUserId, data.site))
    {
        int passInfoDbId = mDb->addEntry(mUserId, data);
        ui->EntrySiteLabel->setText();

        //QList<int> allPassIds = mDb->listAllPassIdsForUserId(mUserId);

        EntryData dataBack = mDb->entryDataForPassId(passInfoDbId);

        //ui->usernameLineEdit->setText(dataBack.username + "Back");
        //ui->websiteLineEdit->setText(dataBack.site + "Back");
        //ui->passwordLineEdit->setText(dataBack.pass + "Back");
        //ui->pinLineEdit->setText(dataBack.pin + "Back");
        //ui->seedEdit->setPlainText(dataBack.seed + "Back");
    }
    else
    {
        data.passId = mDb->getPassId(mUserId, data.site);
        qDebug() << "Current Password ID:" << data.passId;
        mDb->editEntry(data.passId, data);
    }
    */
}
