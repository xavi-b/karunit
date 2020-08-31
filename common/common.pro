TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += core
TARGET          = karunit_common
DESTDIR         = $$PWD

unix {
target.path = /usr/local/lib
INSTALLS += target
}

HEADERS += \
    settings.h \
    defines.h

SOURCES += \
    settings.cpp
