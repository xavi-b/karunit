TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets
TARGET          = emitplugin
DESTDIR         = $$PWD/../app/plugins

LIBS += -L$$PWD/../lib/

LIBS += -lplugininterface
INCLUDEPATH += $$PWD/../plugininterface
DEPENDPATH += $$PWD/../plugininterface

LIBS += -lcommon
INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

SUBDIRS += \
    src/

include(src/src.pri)
