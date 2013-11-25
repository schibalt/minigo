/********************************************************************************
** Form generated from reading UI file 'SetupDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPDIALOG_H
#define UI_SETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *dimensionsBox;
    QLabel *label;
    QComboBox *minMaxBox;
    QLabel *label_2;
    QCheckBox *goFirstBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(388, 132);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 80, 351, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        dimensionsBox = new QSpinBox(Dialog);
        dimensionsBox->setObjectName(QStringLiteral("dimensionsBox"));
        dimensionsBox->setGeometry(QRect(170, 20, 42, 22));
        dimensionsBox->setMinimum(3);
        dimensionsBox->setValue(19);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 20, 61, 16));
        minMaxBox = new QComboBox(Dialog);
        minMaxBox->setObjectName(QStringLiteral("minMaxBox"));
        minMaxBox->setGeometry(QRect(170, 50, 69, 22));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 50, 61, 16));
        goFirstBox = new QCheckBox(Dialog);
        goFirstBox->setObjectName(QStringLiteral("goFirstBox"));
        goFirstBox->setGeometry(QRect(300, 20, 70, 17));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        okButton->setText(QApplication::translate("Dialog", "OK", 0));
        cancelButton->setText(QApplication::translate("Dialog", "Cancel", 0));
        label->setText(QApplication::translate("Dialog", "Dimensions", 0));
        minMaxBox->clear();
        minMaxBox->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "MIN", 0)
         << QApplication::translate("Dialog", "MAX", 0)
        );
        label_2->setText(QApplication::translate("Dialog", "Min/max", 0));
        goFirstBox->setText(QApplication::translate("Dialog", "Go First", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPDIALOG_H
