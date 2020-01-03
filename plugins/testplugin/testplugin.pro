TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets
TARGET          = testplugin
DESTDIR         = $$PWD/../../app/plugins

LIBS += -L$$PWD/../../lib/
LIBS += -L$$PWD/../../app/plugins/

LIBS += -lemitplugin
INCLUDEPATH += $$PWD/../emitplugin/src/
DEPENDPATH += $$PWD/../emitplugin/src/

LIBS += -lplugininterface
INCLUDEPATH += $$PWD/../../plugininterface
DEPENDPATH += $$PWD/../../plugininterface

LIBS += -lcommon
INCLUDEPATH += $$PWD/../../common
DEPENDPATH += $$PWD/../../common

SUBDIRS += \
    src/

include(src/src.pri)

RESOURCES += \
    res/res.qrc
