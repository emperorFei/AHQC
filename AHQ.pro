#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T09:56:29
#
#-------------------------------------------------

QT       += core gui
QT  += sql
QT  += xml
QT  += testlib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AHQ
TEMPLATE = app
CONFIG += debug

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tinyXml2/tinyxml2.cpp \
    test/testreadxmldata.cpp \
    xmlProcessor/myxmlprocessor.cpp \
    #tinyXml2/tinyxml2.cpp
    test/simpletest.cpp \
    util/simpleutil.cpp \
    focusScheme/shiftsscheme.cpp \
    focusScheme/focusscheme.cpp \
    focusScheme/dayboundscheme.cpp \
    focusScheme/obscheme.cpp \
    awsminutedata.cpp \
    singleton.cpp \
    globalseeting.cpp \
    util/sqlfileexecutor.cpp \
    dbcenter.cpp \
    awsminutedaomysqlimp.cpp \
    awsminutedbserver.cpp \
    ahdata.cpp


HEADERS += \
        mainwindow.h \
    test/testreadxmldata.h \
    xmlProcessor/myxmlprocessor.h \
    simpleobject.h \
    tinyXml2/tinyxml2.h \
    test/simpletest.h \
    util/simpleutil.h \
    focusScheme/focusscheme.h \
    focusScheme/shiftsscheme.h \
    focusScheme/dayboundscheme.h \
    focusScheme/obscheme.h \
    solvecncodeproblem.h \
    awsminutedata.h \
    singleton.h \
    globalseeting.h \
    util/sqlfileexecutor.h \
    dbcenter.h \
    awsminutedaomysqlimp.h \
    awsminutedbserver.h \
    ahdata.h


FORMS += \
        mainwindow.ui

RESOURCES += \
    config.qrc
