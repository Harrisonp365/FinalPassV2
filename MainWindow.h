#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "LoginDialog.h"
#include "SignupDialog.h"
#include "DbManager.h"
#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showAllPasswordEntries();

private:
    void createUI();
    void showLoginDialog();
    void richTextToText();


private slots:
    void onSignupRequest();
    void onLoginRequest();
    void listWidgetClicked(QListWidgetItem *item);


    void on_saveButton_clicked();

protected:
    void showEvent(QShowEvent* event) override;

private:
    Ui::MainWindow *ui;
    SignupDialog *mSignupDialog;
    LoginDialog *mLoginDialog = nullptr;
    DbManager* mDb;

    QString mUsername;
    QString mPass;
    int mUserId;
};
#endif // MAINWINDOW_H

