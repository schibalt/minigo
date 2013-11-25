/********************************************************************************
** Form generated from reading UI file 'minigo.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIGO_H
#define UI_MINIGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniGoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiniGoClass)
    {
        if (MiniGoClass->objectName().isEmpty())
            MiniGoClass->setObjectName(QStringLiteral("MiniGoClass"));
        MiniGoClass->resize(600, 400);
        menuBar = new QMenuBar(MiniGoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MiniGoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MiniGoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MiniGoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MiniGoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MiniGoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MiniGoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiniGoClass->setStatusBar(statusBar);

        retranslateUi(MiniGoClass);

        QMetaObject::connectSlotsByName(MiniGoClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniGoClass)
    {
        MiniGoClass->setWindowTitle(QApplication::translate("MiniGoClass", "MiniGo", 0));
    } // retranslateUi

};

namespace Ui {
    class MiniGoClass: public Ui_MiniGoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIGO_H
