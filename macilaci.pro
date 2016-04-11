#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T19:30:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = macilaci
TEMPLATE = app


SOURCES += main.cpp\
        userinterface.cpp \
    game.cpp \
    macilaci.cpp \
    vador.cpp

HEADERS  += userinterface.h \
    macilaci.h \
    vador.h \
    coordinate.h \
    game.h

FORMS    += userinterface.ui
CONFIG += c++11
