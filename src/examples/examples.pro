TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
# LIBS += /usr/local/lib/libjson.a
macx: LIBS += -L/usr/local/lib/ -lformat-json
macx: LIBS += -L/usr/local/lib/ -lformat-json-pointer

SOURCES += \
        main.cpp

HEADERS += \
    usage.h

DISTFILES += \
    ../../README.md
