#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T18:15:07
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = StorageStats
TEMPLATE = lib

DEFINES += STORAGESTATS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    category_catalog.cpp \
    rdb_impl.cpp \
    rdbfactory_impl.cpp \
    storage.cpp \
    query.cpp \
    Config.cpp

HEADERS += \
    category_catalog.h \
    rdb_impl.h \
    rdb.h \
    rdbfactory_impl.h \
    rdbfactory.h \
    domain_filter.h \
    defs.h \
    storage.h \
    query.h \
    Config.h

# path to target
MYTARGET = /usr/local

unix {
    target.path = $${MYTARGET}/include/$$TARGET
    target.files = *.h
    INSTALLS += target
    dlltarget.path = $${MYTARGET}/lib
    dlltarget.files = $$OUT_PWD/*.so*
    INSTALLS += dlltarget
}

# new standard of C++ included
CONFIG += c++11

# install headers path
INCLUDEPATH += $${MYTARGET}/include

# path to dll
LIBS += -L"$${MYTARGET}/lib"
