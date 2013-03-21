QT -= core gui
QMAKE_CXXFLAGS += -std=c++11

TARGET = $PROJNAME

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH +=  Code/include/
INCLUDEPATH += $(GCC_PLS)/include/
LIBS += -L"$$_PRO_FILE_PWD_/libs/"
