TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test/main.cpp
    

HEADERS += \
    public/Constraints.h \
    public/AutoMap.hpp \
    public/VectorMap.hpp

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/public

LIBS += -pthread

