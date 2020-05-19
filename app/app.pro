QT          += core gui widgets
CONFIG      += c++17
DEFINES     += QT_DEPRECATED_WARNINGS
TARGET       = karunit
DESTDIR      = $$PWD

LIBS += -L$$PWD/../plugininterface/ -lplugininterface
INCLUDEPATH += $$PWD/../plugininterface

LIBS += -L$$PWD/../common/ -lcommon
INCLUDEPATH += $$PWD/../common

LIBS += -L$$PWD/../third-party/xblog/ -lxblog
INCLUDEPATH += $$PWD/../third-party/xblog/src

LIBS += -L$$PWD/../third-party/SlidingPanel/lib -lSlidingPanel
INCLUDEPATH += $$PWD/../third-party/SlidingPanel/include

SUBDIRS += \
    src/

include(src/src.pri)

RESOURCES += \
    app.qrc
