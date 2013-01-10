#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T22:00:26
#
#-------------------------------------------------

QT       -= core gui

TARGET = UnitTest11
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS += Code/

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
