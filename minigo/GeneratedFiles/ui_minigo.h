/********************************************************************************
** Form generated from reading UI file 'minigo.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIGO_H
#define UI_MINIGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_MiniGoClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *previewButton;
    QPushButton *moveButton;
    QListWidget *listWidget;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiniGoClass)
    {
        if (MiniGoClass->objectName().isEmpty())
            MiniGoClass->setObjectName(QStringLiteral("MiniGoClass"));
        MiniGoClass->resize(633, 445);
        centralWidget = new QWidget(MiniGoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(240, 10, 380, 380));
        previewButton = new QPushButton(centralWidget);
        previewButton->setObjectName(QStringLiteral("previewButton"));
        previewButton->setGeometry(QRect(110, 340, 75, 23));
        moveButton = new QPushButton(centralWidget);
        moveButton->setObjectName(QStringLiteral("moveButton"));
        moveButton->setGeometry(QRect(20, 340, 75, 23));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 221, 321));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 370, 211, 17));
        progressBar->setValue(24);
        MiniGoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MiniGoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 633, 21));
        MiniGoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MiniGoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MiniGoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MiniGoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiniGoClass->setStatusBar(statusBar);

        retranslateUi(MiniGoClass);

        QMetaObject::connectSlotsByName(MiniGoClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniGoClass)
    {
        MiniGoClass->setWindowTitle(QApplication::translate("MiniGoClass", "MiniGo", 0));
        previewButton->setText(QApplication::translate("MiniGoClass", "Preview Move", 0));
        moveButton->setText(QApplication::translate("MiniGoClass", "Make Move", 0));
    } // retranslateUi

};

namespace Ui {
    class MiniGoClass: public Ui_MiniGoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIGO_H
