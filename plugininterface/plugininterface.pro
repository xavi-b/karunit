TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets bluetooth
TARGET          = plugininterface

LIBS += -L$$PWD/../common/ -lcommon
INCLUDEPATH += $$PWD/../common

LIBS += -L$$PWD/../third-party/xblog/ -lxblog
INCLUDEPATH += $$PWD/../third-party/xblog/src

HEADERS += \
    $$PWD/plugininterface.h \
    bluetoothinterface.h
