QT          += core gui widgets
CONFIG      += c++17
DEFINES     += QT_DEPRECATED_WARNINGS

LIBS += -L$$PWD/../lib/ -lplugininterface
INCLUDEPATH += $$PWD/../plugininterface
DEPENDPATH += $$PWD/../plugininterface

LIBS += -L$$PWD/../lib/ -lcommon
INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

SUBDIRS += \
    src/

include(src/src.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/base.qrc
