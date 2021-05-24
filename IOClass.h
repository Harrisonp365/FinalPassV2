#ifndef IOCLASS_H
#define IOCLASS_H
#include "DbManager.h"
#include <iostream>
#include <QFile>
#include <QTextStream>



class IOClass
{
public:
    IOClass();
    void writeUsername(const QString& username);
    void writePassword(const QString& pass);
    const QString getPassword();
    bool checkPassword(const QString& pass);
    bool confirmPassword(const QString& pass1, const QString& pass2);

private:
    //Do I make these pointers to help passing around the data?
    QString mPassword;
    //DbManager mDb;
};

#endif // IOCLASS_H

