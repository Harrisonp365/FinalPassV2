#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H
#include "DbManager.h"
#include "DbUtils.h"
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
    void userToDb();
    void passwordToStorage();

private:
    QLineEdit* mUserEdit;
    QLineEdit* mPasswordEdit;
    QLineEdit* mPasswordConfirm;
    IOClass*  mIO;
    DbManager mDb;
};

#endif // SIGNUPDIALOG_H
