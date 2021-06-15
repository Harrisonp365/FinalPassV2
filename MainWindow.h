#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "LoginDialog.h"
#include "SignupDialog.h"
#include "DbManager.h"
#include <QMainWindow>


namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void createUI();
    void createConnections();
    void showLoginDialog();
    void displayEntries();

private slots:
    void onSignupRequest();
    void onLoginRequest();

    void on_saveBtn_clicked();

protected:
    void showEvent(QShowEvent* event) override;

private:
    Ui::MainWindow* ui;
    SignupDialog* mSignupDialog;
    LoginDialog* mLoginDialog = nullptr;
    DbManager* mDb;

    QString mUsername;
    QString mPass;
    int mUserId;
};

#endif // MAINWINDOW_H
