#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginDialog.h"
#include "DbManager.h"
#include "DbUtils.h"
#include <QBoxLayout>
#include <QAction>
#include <QLabel>
#include <QListWidgetItem>
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

    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::listWidgetClicked);
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
        showAllPasswordEntries();
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

void MainWindow::showAllPasswordEntries()
{
    mUserId = mDb->getUserId(mUsername);
    QList<int> passIdsToDisplay = mDb->listAllPassIdsForUserId(mUserId);
    qDebug() << "All Password entries to be displayed:" << passIdsToDisplay;

    for(int i = 0; i < passIdsToDisplay.size(); i++)
    {
        EntryData dataBack = mDb->entryDataForPassId(passIdsToDisplay[i]);
        qDebug() << "Entry data getting from 4loop: " << dataBack.site;
        ui->listWidget->addItem(dataBack.site);
    }

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
     mUserId = mDb->getUserId(mUsername);
     EntryData data;
     data.username = ui->usernameLineEdit->text();
     data.site = ui->websiteLineEdit->text();
     data.pass = ui->passwordLineEdit->text();
     data.pin = ui->pinLineEdit->text();
     data.seed = ui->seedEdit->toPlainText();

    if(!mDb->entryExists(mUserId, data.site))
    {
        int passInfoDbId = mDb->addEntry(mUserId, data);


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
        data.id = mDb->getPassId(mUserId, data.site);
        qDebug() << "Current Password ID:" << data.id;
        mDb->editEntry(data.id, data);
    }  

}

void MainWindow::listWidgetClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
}
