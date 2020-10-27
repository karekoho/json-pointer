CONFIG -= qt

TEMPLATE = lib
DEFINES += JSON_POINTER_LIBRARY

CONFIG += c++11

INCLUDEPATH += /usr/local/include

#LIBS += -L/usr/local/lib -ljson
LIBS += /usr/local/lib/libjson.a
LIBS += -L/usr/local/lib -lgtest -lpthread

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    json_pointer.cpp

HEADERS += \
    json_exception.h \
    json_pointer_global.h \
    json_pointer.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
