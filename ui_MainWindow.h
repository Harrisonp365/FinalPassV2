/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/qaction.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBackUp;
    QAction *actionEXit;
    QAction *actionFind;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *leftVerticalLayout;
    QLabel *label_4;
    QListView *listView;
    QWidget *formLayoutWidget;
    QFormLayout *rightFormLayout;
    QLabel *label;
    QLineEdit *webSite;
    QLabel *label_2;
    QLineEdit *userName;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_7;
    QPlainTextEdit *plainTextEdit;
    QLineEdit *lineEdit_3;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuTools;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(535, 536);
        actionBackUp = new QAction(MainWindow);
        actionBackUp->setObjectName(QString::fromUtf8("actionBackUp"));
        actionEXit = new QAction(MainWindow);
        actionEXit->setObjectName(QString::fromUtf8("actionEXit"));
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(500, 500));
        centralWidget->setBaseSize(QSize(500, 500));
        centralWidget->setMouseTracking(false);
        centralWidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        leftVerticalLayout = new QVBoxLayout(verticalLayoutWidget);
        leftVerticalLayout->setObjectName(QString::fromUtf8("leftVerticalLayout"));
        leftVerticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        leftVerticalLayout->addWidget(label_4);

        listView = new QListView(verticalLayoutWidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        leftVerticalLayout->addWidget(listView);

        splitter->addWidget(verticalLayoutWidget);
        formLayoutWidget = new QWidget(splitter);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        rightFormLayout = new QFormLayout(formLayoutWidget);
        rightFormLayout->setObjectName(QString::fromUtf8("rightFormLayout"));
        rightFormLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        rightFormLayout->setWidget(0, QFormLayout::LabelRole, label);

        webSite = new QLineEdit(formLayoutWidget);
        webSite->setObjectName(QString::fromUtf8("webSite"));

        rightFormLayout->setWidget(0, QFormLayout::FieldRole, webSite);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        rightFormLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        userName = new QLineEdit(formLayoutWidget);
        userName->setObjectName(QString::fromUtf8("userName"));

        rightFormLayout->setWidget(1, QFormLayout::FieldRole, userName);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        rightFormLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        rightFormLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        lineEdit_4 = new QLineEdit(formLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        rightFormLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_4);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        rightFormLayout->setWidget(4, QFormLayout::LabelRole, label_7);

        plainTextEdit = new QPlainTextEdit(formLayoutWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        rightFormLayout->setWidget(4, QFormLayout::FieldRole, plainTextEdit);

        lineEdit_3 = new QLineEdit(formLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        rightFormLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_3);

        splitter->addWidget(formLayoutWidget);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 535, 18));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionBackUp);
        menuFile->addSeparator();
        menuFile->addAction(actionEXit);
        menuHelp->addAction(actionAbout);
        menuTools->addAction(actionFind);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionBackUp->setText(QCoreApplication::translate("MainWindow", "&Back Up...", nullptr));
        actionEXit->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "&Find", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Currently stored Passwords", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Website", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Pin", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Seed Phrase", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "&Help", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "&Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
