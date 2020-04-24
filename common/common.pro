TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += core
TARGET          = common

HEADERS += \
    settings.h \
    defines.h

SOURCES += \
    settings.cpp
