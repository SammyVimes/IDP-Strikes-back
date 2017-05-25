#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T00:59:29
#
#-------------------------------------------------

QT       += core gui xml

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mdp_strikes_back
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dfdelement.cpp \
    exception.cpp \
    displayabledfdelement.cpp \
    clickableellipseitem.cpp \
    planwindow.cpp \
    addpilldialog.cpp \
    addfooddialog.cpp \
    food.cpp \
    pill.cpp \
    eatingprocess.cpp \
    cookingprocess.cpp \
    medsprocess.cpp \
    pillcheckbox.cpp \
    checkboxfabric.cpp \
    foodcheckbox.cpp \
    plan.cpp \
    startdialog.cpp \
    planfilesmanager.cpp

HEADERS  += mainwindow.h \
    directedgraph.h \
    dfdelement.h \
    exception.h \
    displayabledfdelement.h \
    clickableellipseitem.h \
    planwindow.h \
    addpilldialog.h \
    addfooddialog.h \
    food.h \
    pill.h \
    eatingprocess.h \
    cookingprocess.h \
    medsprocess.h \
    pillcheckbox.h \
    checkboxfabric.h \
    foodcheckbox.h \
    plan.h \
    startdialog.h \
    planfilesmanager.h

FORMS    += mainwindow.ui \
    planwindow.ui \
    addpilldialog.ui \
    addfooddialog.ui \
    startdialog.ui
