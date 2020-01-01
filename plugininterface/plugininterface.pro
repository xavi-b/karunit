TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets
TARGET          = plugininterface
DESTDIR         = $$PWD/../lib

LIBS += -L$$PWD/../lib/ -lcommon
INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

HEADERS += \
    $$PWD/plugininterface.h
