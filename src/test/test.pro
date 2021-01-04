TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
LIBS += -L/usr/local/lib -lgtest -lpthread
LIBS += /usr/local/lib/libjson.a
#macx: LIBS += -L/usr/local/lib/ -ljson

SOURCES += \
        ../json_pointer/json_pointer.cpp \
        main.cpp

HEADERS += \
    ../json_pointer/json_pointer.h \
    json_pointer_test.h \
    unit_test.h
