#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T14:35:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mylittlepaint
TEMPLATE = app

QT += printsupport
QT += widgets

SOURCES += main.cpp\
        mainwindow.cpp \
    modele.cpp \
    controle.cpp

HEADERS  += \
    mainwindow.h \
    modele.h \
    controle.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
