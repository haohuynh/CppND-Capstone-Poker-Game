/********************************************************************************
** Form generated from reading UI file 'bankroll.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANKROLL_H
#define UI_BANKROLL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BankRoll
{
public:
    QSpinBox *spinBox;
    QSlider *horizontalSlider;
    QLabel *bkRLbl;
    QPushButton *doneButton;

    void setupUi(QDialog *BankRoll)
    {
        if (BankRoll->objectName().isEmpty())
            BankRoll->setObjectName(QString::fromUtf8("BankRoll"));
        BankRoll->resize(400, 170);
        spinBox = new QSpinBox(BankRoll);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(30, 90, 51, 21));
        horizontalSlider = new QSlider(BankRoll);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(120, 90, 251, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        bkRLbl = new QLabel(BankRoll);
        bkRLbl->setObjectName(QString::fromUtf8("bkRLbl"));
        bkRLbl->setGeometry(QRect(20, 20, 351, 51));
        bkRLbl->setScaledContents(true);
        bkRLbl->setWordWrap(true);
        bkRLbl->setOpenExternalLinks(false);
        doneButton = new QPushButton(BankRoll);
        doneButton->setObjectName(QString::fromUtf8("doneButton"));
        doneButton->setGeometry(QRect(160, 130, 75, 23));

        retranslateUi(BankRoll);

        QMetaObject::connectSlotsByName(BankRoll);
    } // setupUi

    void retranslateUi(QDialog *BankRoll)
    {
        BankRoll->setWindowTitle(QApplication::translate("BankRoll", "Bank Roll", nullptr));
        bkRLbl->setText(QApplication::translate("BankRoll", "TextLabel", nullptr));
        doneButton->setText(QApplication::translate("BankRoll", "Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BankRoll: public Ui_BankRoll {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANKROLL_H
