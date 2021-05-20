#include "IOClass.h"
#include <QDebug>
#include <QMessageBox>
#include "SignupDialog.h"

IOClass::IOClass()
{

}

void IOClass::writePassword(const QString& pass)
{
    QFile file("pass.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << pass;
    file.close();
    qDebug() << "pass in file is:" << pass;
}

const QString IOClass::getPassword()
{
    QFile file("pass.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Could not open file for reading";

    QTextStream in(&file);
    QString line = in.readLine(0);
    qDebug() << line;
    mPassword = line;
    file.close();

    return mPassword;
}

bool IOClass::checkPassword(const QString& pass)
{
    qDebug() <<"pass is:" << pass;
    qDebug() << "mPassword is:" << mPassword;

    if(pass == mPassword)
        return true;
    else
        return false;
}

bool IOClass::confirmPassword(const QString& pass1, const QString& pass2)
{
    if(pass1 == pass2)
        return true;
    else
        return false;
}
