TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
#LIBS += /usr/local/lib/libjson.a
macx: LIBS += -L/usr/local/lib/ -ljson
macx: LIBS += -L/usr/local/lib/ -ljson_pointer

SOURCES += \
        main.cpp

HEADERS += \
    usage.h
