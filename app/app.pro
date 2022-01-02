QT          += core gui quick
CONFIG      += c++17
DEFINES     += QT_DEPRECATED_WARNINGS
TARGET       = karunit
DESTDIR      = $$PWD

unix {
target.path = /usr/local/bin
INSTALLS += target
}

LIBS += -L$$PWD/../plugininterface/ -lkarunit_plugininterface
INCLUDEPATH += $$PWD/../plugininterface

LIBS += -L$$PWD/../common/ -lkarunit_common
INCLUDEPATH += $$PWD/../common

LIBS += -L$$PWD/../third-party/xblog/lib -lxblog
INCLUDEPATH += $$PWD/../third-party/xblog/include

SUBDIRS += \
    src/ \
    res/

include(src/src.pri)
include(res/res.pri)

debug {
CONFIG += console
}
