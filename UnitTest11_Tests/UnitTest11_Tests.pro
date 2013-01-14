TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
debug:CONFIG -= release

INCLUDEPATH += ../UnitTest11/Code/include/

SOURCES += \
    Code/main.cpp \
    Code/Bootstrap/WillThrowTests.cpp \
    Code/Bootstrap/MockReturnHandlerTests.cpp \
    Code/Bootstrap/MockTests.cpp \
    Code/Bootstrap/TestStageTests.cpp \
    Code/Bootstrap/TestStageBuilderTests.cpp \
    Code/Bootstrap/WillPassTests.cpp \
    Code/Bootstrap/TestFixtureTests.cpp \
    Code/Bootstrap/TestFixtureRunnerTests.cpp \
    Code/Unit/AssertFailTests.cpp \
    Code/Unit/IsEqualToTests.cpp \
    Code/Unit/AssertThatTests.cpp \
    Code/Unit/IsFalseTests.cpp \
    Code/Unit/IsTrueTests.cpp \
    Code/Unit/IsOperandTests.cpp \
    Code/Unit/MockArgumentHandlerTests.cpp

debug:LIBS += -L$$OUT_PWD/debug
release:LIBS += -L$$OUT_PWD/release

LIBS += -lUnitTest11 -lUnitTest++
