#-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T07:52:46
#
#-------------------------------------------------

QT       += core gui \
        multimedia
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PokerGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    uicontroller.cpp \
    mainscene.cpp \
    pokerhelper.cpp \
    pokerpushbutton.cpp \
    pokercardtable.cpp \
    bankroll.cpp \
    pokerclient.cpp

HEADERS  += mainwindow.h \
    uicontroller.h \
    mainscene.h \
    pokerhelper.h \
    pokerpushbutton.h \
    pokercardtable.h \
    bankroll.h \
    pokerclient.h


FORMS    += mainwindow.ui \
    bankroll.ui

RESOURCES += \
    images.qrc \
    soundtracks.qrc


