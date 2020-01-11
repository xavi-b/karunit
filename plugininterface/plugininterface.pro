TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets bluetooth
TARGET          = plugininterface
DESTDIR         = $$PWD/../lib

LIBS += -L$$PWD/../lib/

LIBS += -lcommon
INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

HEADERS += \
    $$PWD/plugininterface.h \
    bluetoothinterface.h
