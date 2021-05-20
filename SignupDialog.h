#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>

class IOClass;
class QLineEdit;

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = nullptr);
    ~SignupDialog();

private:


private slots:
    void createUI();
    bool confirmSignupPassword();

private:
    void passwordToStorage();

private:
    QLineEdit* mPasswordEdit;
    QLineEdit* mPasswordConfirm;
    IOClass*  mIO;
};

#endif // SIGNUPDIALOG_H
