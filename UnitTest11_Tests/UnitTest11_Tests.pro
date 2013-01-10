TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += ../UnitTest11/Code/include/

SOURCES += \
    Code/main.cpp \
    Code/Bootstrap/CopiedPtrTests.cpp

LIBS += -lUnitTest++
