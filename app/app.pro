QT          += core gui widgets
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

LIBS += -L$$PWD/../third-party/SlidingPanel/lib -lSlidingPanel
INCLUDEPATH += $$PWD/../third-party/SlidingPanel/include

SUBDIRS += \
    src/

include(src/src.pri)

RESOURCES += \
    app.qrc

debug {
CONFIG += console
}
