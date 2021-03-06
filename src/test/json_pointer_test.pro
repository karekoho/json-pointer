TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = test_debug

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
LIBS += -L/usr/local/lib -lgtest -lpthread
#LIBS += /usr/local/lib/libjson.a
macx: LIBS += -L/usr/local/lib/ -lformat-json

SOURCES += \
        ../json_pointer/json_pointer.cpp \
        main.cpp

HEADERS += \
    ../json_pointer/json_pointer.h \
    ../json_pointer/json_pointer_exception.h \
    json_pointer_test.h \
    unit_test.h

DISTFILES += \
    ../../CMakeLists.txt \
    ../../README.md \
    ../../build/macos/test/release/CMakeLists.txt
