CONFIG -= qt

TEMPLATE = lib
DEFINES += JSON_POINTER_LIBRARY

CONFIG += c++11

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

macx: LIBS += -L/usr/local/lib/ -ljson
#LIBS += /usr/local/lib/libjson.a


SOURCES += \
    json_pointer.cpp

HEADERS += \
    json_pointer_exception.h \
    json_pointer_global.h \
    json_pointer.h

# Default rules for deployment.
unix {
    target.path = /usr/local/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../CMakeLists.txt \
    ../../README.md \
    CMakeLists.txt
