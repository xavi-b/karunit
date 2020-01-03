TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += core
TARGET          = common
DESTDIR         = $$PWD/../lib

HEADERS += \
    $$PWD/log.h \
    $$PWD/logger.h \
    $$PWD/settings.h \
    defines.h

SOURCES += \
    $$PWD/logger.cpp \
    $$PWD/settings.cpp
