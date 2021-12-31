TEMPLATE        = lib
CONFIG         += plugin c++17
DEFINES        += QT_DEPRECATED_WARNINGS
TARGET          = karunit_plugininterface
DESTDIR         = $$PWD

unix {
target.path = /usr/local/lib
INSTALLS += target
}

LIBS += -L$$PWD/../common/ -lkarunit_common
INCLUDEPATH += $$PWD/../common

LIBS += -L$$PWD/../third-party/xblog/lib -lxblog
INCLUDEPATH += $$PWD/../third-party/xblog/include

HEADERS += \
    $$PWD/plugininterface.h
