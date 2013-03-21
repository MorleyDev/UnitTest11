CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
debug:CONFIG -= release

INCLUDEPATH += ../$PROJNAME/Code/include/
INCLUDEPATH += $(GCC_PLS)/include/

SOURCES += Code/main.cpp

debug:LIBS += -L$$OUT_PWD/debug
release:LIBS += -L$$OUT_PWD/release
LIBS += -L$(GCC_PLS)/lib/

LIBS += -l$PROJNAME -lUnitTest11
