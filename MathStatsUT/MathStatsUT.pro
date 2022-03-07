#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T23:49:54
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_anovatest
CONFIG   += console
CONFIG   -= app_bundle

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


SOURCES += tst_anovatest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

# path to target
MYTARGET = /usr/local

# new standard of C++ included
CONFIG += c++11

# install headers path
INCLUDEPATH += $${MYTARGET}/include

# path to dll
LIBS += -L"$${MYTARGET}/lib"
LIBS += -lMathStats -lgsl -lgslcblas
