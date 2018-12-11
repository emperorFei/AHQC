CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(mydoublelabelplugin)
TEMPLATE    = lib

HEADERS     = mydoublelabelplugin.h \
    mydoublelabel.h
SOURCES     = mydoublelabelplugin.cpp \
    mydoublelabel.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(mydoublelabel.pri)

FORMS += \
    mydoublelabel.ui
