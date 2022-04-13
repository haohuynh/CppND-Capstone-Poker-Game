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


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/uicontroller.cpp \
    src/mainscene.cpp \
    src/pokerhelper.cpp \
    src/pokerpushbutton.cpp \
    src/pokercardtable.cpp \
    src/bankroll.cpp \
    src/pokerclient.cpp

HEADERS  += src/mainwindow.h \
    src/uicontroller.h \
    src/mainscene.h \
    src/pokerhelper.h \
    src/pokerpushbutton.h \
    src/pokercardtable.h \
    src/bankroll.h \
    src/pokerclient.h


FORMS    += src/mainwindow.ui \
    src/bankroll.ui

RESOURCES += \
    src/images.qrc \
    src/soundtracks.qrc

