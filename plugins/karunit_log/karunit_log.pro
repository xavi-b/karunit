TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets
TARGET          = karunit_log_plugin
DESTDIR         = $$PWD/../../app/plugins

unix {
target.path = /usr/local/bin/plugins
INSTALLS += target
}

LIBS += -L$$PWD/../../plugininterface/ -lkarunit_plugininterface
INCLUDEPATH += $$PWD/../../plugininterface

LIBS += -L$$PWD/../../common/ -lkarunit_common
INCLUDEPATH += $$PWD/../../common

LIBS += -L$$PWD/../../third-party/xblog/lib -lxblog
INCLUDEPATH += $$PWD/../../third-party/xblog/include

SUBDIRS += \
    src/

include(src/src.pri)

RESOURCES += \
    karunit_log.qrc
