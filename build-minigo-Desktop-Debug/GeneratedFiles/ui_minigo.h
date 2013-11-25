/********************************************************************************
** Form generated from reading UI file 'minigo.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
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

class Ui_minigoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *minigoClass)
    {
        if (minigoClass->objectName().isEmpty())
            minigoClass->setObjectName(QStringLiteral("minigoClass"));
        minigoClass->resize(600, 400);
        menuBar = new QMenuBar(minigoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        minigoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(minigoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        minigoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(minigoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        minigoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(minigoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        minigoClass->setStatusBar(statusBar);

        retranslateUi(minigoClass);

        QMetaObject::connectSlotsByName(minigoClass);
    } // setupUi

    void retranslateUi(QMainWindow *minigoClass)
    {
        minigoClass->setWindowTitle(QApplication::translate("minigoClass", "minigo", 0));
    } // retranslateUi

};

namespace Ui {
    class minigoClass: public Ui_minigoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIGO_H
