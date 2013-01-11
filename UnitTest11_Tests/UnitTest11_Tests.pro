TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
debug:CONFIG -= release

INCLUDEPATH += ../UnitTest11/Code/include/

SOURCES += \
    Code/main.cpp \
    Code/Bootstrap/CopiedPtrTests.cpp \
    Code/Bootstrap/AssertFailTests.cpp

debug:LIBS += -L$$OUT_PWD/debug
release:LIBS += -L$$OUT_PWD/release

LIBS += -lUnitTest++ -lUnitTest11
