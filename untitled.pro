#-------------------------------------------------
#
# Project created by QtCreator 2014-08-06T08:31:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mymodel.cpp

HEADERS  += mainwindow.h \
    mymodel.h  \
    communicate.h

FORMS    += mainwindow.ui

QT += sql
