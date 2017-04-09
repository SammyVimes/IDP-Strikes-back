#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T00:59:29
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mdp_strikes_back
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dotgenerator.cpp \
    dfdelement.cpp \
    exception.cpp

HEADERS  += mainwindow.h \
    directedgraph.h \
    dotgenerator.h \
    dfdelement.h \
    exception.h

FORMS    += mainwindow.ui
