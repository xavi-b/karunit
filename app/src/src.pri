SUBDIRS += \
    widgets/

include(widgets/widgets.pri)

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/splashscreen.cpp

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/splashscreen.h
