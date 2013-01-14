TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
debug:CONFIG -= release

INCLUDEPATH += ../UnitTest11/Code/include/

SOURCES += \
    Code/main.cpp \
    Code/Bootstrap/AssertThatTests.cpp \
    Code/Bootstrap/IsEqualToTests.cpp \
    Code/Bootstrap/IsOperandTests.cpp \
    Code/Bootstrap/WillThrowTests.cpp \
    Code/Bootstrap/MockReturnHandlerTests.cpp \
    Code/Bootstrap/MockArgumentHandlerTests.cpp \
    Code/Bootstrap/MockTests.cpp \
    Code/Bootstrap/TestStageTests.cpp \
    Code/Bootstrap/TestStageBuilderTests.cpp \
    Code/Bootstrap/WillPassTests.cpp \
    Code/Bootstrap/TestFixtureTests.cpp \
    Code/Bootstrap/TestFixtureRunnerTests.cpp \
    Code/AssertFailTests.cpp

debug:LIBS += -L$$OUT_PWD/debug
release:LIBS += -L$$OUT_PWD/release

LIBS += -lUnitTest11 -lUnitTest++
