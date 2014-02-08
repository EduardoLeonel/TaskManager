#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T14:59:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaskManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taskmanager.cpp \
    task.cpp

HEADERS  += mainwindow.h \
    taskmanager.h \
    task.h

FORMS    += mainwindow.ui
