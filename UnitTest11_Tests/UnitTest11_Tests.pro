TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
debug:CONFIG -= release

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ../UnitTest11/Code/include/

SOURCES += \
    Code/main.cpp
    
SOURCES += \
    Code/Unit/AssertFailTests.cpp \
    Code/Unit/AssertThatTests.cpp \
    Code/Unit/IsAnyTests.cpp \
    Code/Unit/IsBetweenTests.cpp \
    Code/Unit/IsEqualToTests.cpp \
    Code/Unit/IsFalseTests.cpp \
    Code/Unit/IsGreaterThanTests.cpp \
    Code/Unit/IsInfinityTests.cpp \
    Code/Unit/IsLessThanTests.cpp \
    Code/Unit/IsNaNTests.cpp \
    Code/Unit/IsNullTests.cpp \
    Code/Unit/IsOperandTests.cpp \
    Code/Unit/IsStringContainingTests.cpp \
    Code/Unit/IsTrueTests.cpp \
    Code/Unit/IsZeroTests.cpp \
    Code/Unit/MockArgumentHandlerTests.cpp \
    Code/Unit/MockReturnHandlerTests.cpp \
    Code/Unit/MockTests.cpp \
    Code/Unit/TestFixtureRunnerTests.cpp \
    Code/Unit/TestFixtureTests.cpp \
    Code/Unit/TestStageBuilderTests.cpp \
    Code/Unit/TestStageTests.cpp \
    Code/Unit/WillPassTests.cpp \
    Code/Unit/WillThrowTests.cpp
    
SOURCES += \
	Code/Examples/Minesweeper.cpp

debug:LIBS += -L$$OUT_PWD/debug
release:LIBS += -L$$OUT_PWD/release

LIBS += -lUnitTest11
