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
#CONFIG += qt release warn_off
CONFIG += qt debug  warn_off

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
    ahdata.cpp \
    zdata.cpp \
    util/dataformatutil.cpp \
    test/qtfeaturetest.cpp \
    settingwidget.cpp \
    nofocusframedelegate.cpp \
    ahqlistwidgetitem.cpp \
    zdatadaomysqlimp.cpp \
    azdata.cpp \
    fullwidegt.cpp \
    horizontaltree.cpp \
    animationstackedwidget.cpp \
    ui/calendarwidget.cpp \
    ui/clickablelabel.cpp \
    ui/date.cpp \
    ui/daylabel.cpp \
    ui/hourlabel.cpp \
    ui/datetimedialog.cpp \
    ui/datetimerangeselectdialog.cpp \
    ui/datetimepagenumberwidget.cpp \
    ui/signeddaylabel.cpp \
    ui/signedhourlabel.cpp


HEADERS += \
        mainwindow.h \
    test/testreadxmldata.h \
    test/simpletest.h \
    test/qtfeaturetest.h \
    xmlProcessor/myxmlprocessor.h \    
    tinyXml2/tinyxml2.h \
    util/dataformatutil.h \
    util/simpleutil.h \
    util/sqlfileexecutor.h \
    focusScheme/focusscheme.h \
    focusScheme/shiftsscheme.h \
    focusScheme/dayboundscheme.h \
    focusScheme/obscheme.h \
    simpleobject.h \
    solvecncodeproblem.h \
    awsminutedata.h \
    singleton.h \
    globalseeting.h \
    dbcenter.h \
    awsminutedaomysqlimp.h \
    awsminutedbserver.h \
    ahdata.h \
    zdata.h \
    settingwidget.h \
    nofocusframedelegate.h \
    ahqlistwidgetitem.h \
    zdatadaomysqlimp.h \
    azdata.h \
    fullwidegt.h \
    horizontaltree.h \
    animationstackedwidget.h \
    ui/calendarwidget.h \
    ui/clickablelabel.h \
    ui/date.h \
    ui/daylabel.h \
    ui/hourlabel.h \
    ui/datetimedialog.h \
    ui/datetimerangeselectdialog.h \
    ui/datetimepagenumberwidget.h \
    enums.h \
    ui/signeddaylabel.h \
    ui/signedhourlabel.h




FORMS += \
        mainwindow.ui \
    settingwidget.ui \
    fullwidegt.ui \
    horizontaltree.ui \
    animationstackedwidget.ui

RESOURCES += \
    config.qrc \
    ico.qrc
DEPENDPATH += $$PWD/lib
DISTFILES += \
    configs/ItemCols.xml \
    configs/dataSetting.ini \
    configs/uiSetting.ini

#LIBS += $$PWD/lib/libmydoublelabelplugin.a
LIBS += $$PWD/lib/libmydoublelabelplugind.a
#LIBS += $$PWD/lib/mydoublelabelplugin.lib
INCLUDEPATH += $$PWD/include


