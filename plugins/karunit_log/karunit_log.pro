TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets
TARGET          = karunit_log_plugin
DESTDIR         = $$PWD/../../app/plugins

LIBS += -L$$PWD/../../plugininterface/ -lplugininterface
INCLUDEPATH += $$PWD/../../plugininterface

LIBS += -L$$PWD/../../common/ -lcommon
INCLUDEPATH += $$PWD/../../common

LIBS += -L$$PWD/../../third-party/xblog/ -lxblog
INCLUDEPATH += $$PWD/../../third-party/xblog/src

SUBDIRS += \
    src/

include(src/src.pri)

RESOURCES += \
    karunit_log.qrc
