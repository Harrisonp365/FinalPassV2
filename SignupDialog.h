#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H
#include "DbManager.h"
//#include "DbUtils.h"
#include <QDialog>


class IOClass;
class QLineEdit;

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = nullptr);
    ~SignupDialog();

private slots:
    void createUI();
    void confirmSignup();

private:
    void userToDb();
    void passwordToDb();

private:
    QLineEdit* mUserEdit;
    QLineEdit* mPasswordEdit;
    QLineEdit* mPasswordConfirm;
    IOClass*  mIO;
    DbManager* mDb;
};

#endif // SIGNUPDIALOG_H
