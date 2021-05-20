#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LoginDialog.h"
#include "SignupDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createUI();

private slots:
    void onSignupRequest();
    void onLoginRequest();

private:
    Ui::MainWindow *ui;
    SignupDialog *mSignupDialog;
    LoginDialog *mLoginDialog;
};
#endif // MAINWINDOW_H
