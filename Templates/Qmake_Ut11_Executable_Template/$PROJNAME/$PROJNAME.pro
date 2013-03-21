QT -= core gui
QMAKE_CXXFLAGS += -std=c++11

TARGET = $PROJNAME

CONFIG(test) {
	TEMPLATE = app
	CONFIG += console
	CONFIG -= app_bundle
	CONFIG -= qt
}
else {
	TEMPLATE = lib
	CONFIG += dll
}

INCLUDEPATH +=  Code/include/
INCLUDEPATH += $(GCC_PLS)/include/
LIBS += -L"$$_PRO_FILE_PWD_/libs/"

SOURCES += Code/src/main.cpp
