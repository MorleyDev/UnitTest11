TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
debug:CONFIG -= release

INCLUDEPATH += ../UnitTest11/Code/include/

SOURCES += \
    Code/main.cpp \
    Code/Bootstrap/MockReturnHandlerTests.cpp \
    Code/Bootstrap/MockTests.cpp \
    Code/Bootstrap/TestFixtureTests.cpp \
    Code/Bootstrap/TestFixtureRunnerTests.cpp \
    Code/Unit/AssertFailTests.cpp \
    Code/Unit/IsEqualToTests.cpp \
    Code/Unit/AssertThatTests.cpp \
    Code/Unit/IsFalseTests.cpp \
    Code/Unit/IsTrueTests.cpp \
    Code/Unit/IsOperandTests.cpp \
    Code/Unit/MockArgumentHandlerTests.cpp \
    Code/Unit/WillPassTests.cpp \
    Code/Unit/WillThrowTests.cpp \
    Code/Unit/IsAnyTests.cpp \
    Code/Unit/IsZeroTests.cpp \
    Code/Unit/TestStageTests.cpp \
    Code/Unit/TestStageBuilderTests.cpp

debug:LIBS += -L$$OUT_PWD/debug
release:LIBS += -L$$OUT_PWD/release

LIBS += -lUnitTest11 -lUnitTest++
