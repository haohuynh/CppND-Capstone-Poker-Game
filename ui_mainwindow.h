/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Game;
    QAction *actionSave;
    QAction *actionLoad_Game;
    QAction *actionExit;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QLabel *bkLabel;
    QLabel *betLabel;
    QLCDNumber *bkLCD;
    QLCDNumber *betLCD;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuGame;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 600);
        MainWindow->setMaximumSize(QSize(1000, 600));
        actionNew_Game = new QAction(MainWindow);
        actionNew_Game->setObjectName(QString::fromUtf8("actionNew_Game"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionLoad_Game = new QAction(MainWindow);
        actionLoad_Game->setObjectName(QString::fromUtf8("actionLoad_Game"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(22, 10, 950, 570));
        graphicsView->setMaximumSize(QSize(950, 570));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        bkLabel = new QLabel(centralWidget);
        bkLabel->setObjectName(QString::fromUtf8("bkLabel"));
        bkLabel->setGeometry(QRect(90, 150, 91, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        bkLabel->setFont(font);
        bkLabel->setScaledContents(false);
        betLabel = new QLabel(centralWidget);
        betLabel->setObjectName(QString::fromUtf8("betLabel"));
        betLabel->setGeometry(QRect(90, 180, 101, 20));
        betLabel->setFont(font);
        bkLCD = new QLCDNumber(centralWidget);
        bkLCD->setObjectName(QString::fromUtf8("bkLCD"));
        bkLCD->setGeometry(QRect(214, 150, 64, 23));
        betLCD = new QLCDNumber(centralWidget);
        betLCD->setObjectName(QString::fromUtf8("betLCD"));
        betLCD->setGeometry(QRect(214, 180, 64, 23));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QString::fromUtf8("menuGame"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuGame->menuAction());
        menuGame->addAction(actionNew_Game);
        menuGame->addAction(actionSave);
        menuGame->addAction(actionLoad_Game);
        menuGame->addSeparator();
        menuGame->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PokerGame", nullptr));
        actionNew_Game->setText(QApplication::translate("MainWindow", "New Game", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save Bank Roll", nullptr));
        actionLoad_Game->setText(QApplication::translate("MainWindow", "Load Bank Roll", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        bkLabel->setText(QApplication::translate("MainWindow", "BankRoll:", nullptr));
        betLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Bet:</p></body></html>", nullptr));
        menuGame->setTitle(QApplication::translate("MainWindow", "Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
