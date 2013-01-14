#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T22:00:26
#
#-------------------------------------------------

QT       -= core gui

TARGET = UnitTest11
TEMPLATE = lib
CONFIG += staticlib
debug:CONFIG -= release

SOURCES += \
    Code/src/Assert/Fail.cpp \
    Code/src/Utility/TestStage.cpp \
    Code/src/TestFixture.cpp \
    Code/src/TestFixtureRunner.cpp \
    Code/src/Global.cpp \
    Code/src/Is/True.cpp \
    Code/src/Is/False.cpp

HEADERS += \
    Code/include/UnitTest11.hpp \
    Code/include/UnitTest11/TestFailedException.hpp \
    Code/include/UnitTest11/Assert/Fail.hpp \
    Code/include/UnitTest11/Utility/BaseOperand.hpp \
    Code/include/UnitTest11/Assert/That.hpp \
    Code/include/UnitTest11/Utility/ToString.hpp \
    Code/include/UnitTest11/Utility/AreEqual.hpp \
    Code/include/UnitTest11/Is/EqualTo.hpp \
    Code/include/UnitTest11/Will/Throw.hpp \
    Code/include/UnitTest11/Utility/DefaultValue.hpp \
    Code/include/UnitTest11/Utility/MockArgumentHandler.hpp \
    Code/include/UnitTest11/Utility/MockReturnHandler.hpp \
    Code/include/UnitTest11/Mock.hpp \
    Code/include/UnitTest11/IOutput.hpp \
    Code/include/UnitTest11/Utility/TestStage.hpp \
    Code/include/UnitTest11/Utility/TestStageBuilder.hpp \
    Code/include/UnitTest11/Will/Pass.hpp \
    Code/include/UnitTest11/TestFixture.hpp \
    Code/include/UnitTest11/TestFixtureRunner.hpp \
    Code/include/UnitTest11/Global.hpp \
    Code/include/UnitTest11/StdOutput.hpp \
    Code/include/UnitTest11/Macros.hpp \
    Code/include/UnitTest11/Is/True.hpp \
    Code/include/UnitTest11/Is/False.hpp

INCLUDEPATH +=  Code/include/

win32 {
    win32-g++:LIBS += -L"$$_PRO_FILE_PWD_/libs/"
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
