#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T12:41:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FootballTour
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    informationwindow.cpp \
    adminwindow.cpp \
    noteditabledelegate.cpp \
    addnewsouvenir.cpp \
    filebrowerdiag.cpp \
    logindialog.cpp \
    customtrip.cpp \
    purchasesouvenirs.cpp \
    tripfromcoliseum.cpp \
    tripfromfoldfield.cpp \
    graph.cpp

HEADERS  += mainwindow.h \
    database.h \
    informationwindow.h \
    adminwindow.h \
    noteditabledelegate.h \
    addnewsouvenir.h \
    filebrowerdiag.h \
    logindialog.h \
    customtrip.h \
    purchasesouvenirs.h \
    tripfromcoliseum.h \
    tripfromfoldfield.h \
    graph.h

FORMS    += mainwindow.ui \
    informationwindow.ui \
    adminwindow.ui \
    addnewsouvenir.ui \
    filebrowerdiag.ui \
    logindialog.ui \
    customtrip.ui \
    purchasesouvenirs.ui \
    tripfromcoliseum.ui \
    tripfromfoldfield.ui

RESOURCES += \
    res.qrc
