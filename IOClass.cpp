#include "IOClass.h"
#include "SignupDialog.h"
#include <QDebug>
#include <QMessageBox>


IOClass::IOClass()
{

}

bool IOClass::confirmPassword(const QString& pass1, const QString& pass2)
{
    return pass1 == pass2;
}
