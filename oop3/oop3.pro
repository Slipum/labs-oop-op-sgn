QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    ./src/main.cpp \
    ./src/interface/mainwindow.cpp \
    ./src/bussines/calculator.cpp

HEADERS += \
    ./src/interface/mainwindow.h \
    ./src/bussines/calculator.h

FORMS += \
    ./src/interface/mainwindow.ui

# Фикс для Qt 6.9.2 macOS ARM (__yield ошибка)
QMAKE_CXXFLAGS += -Wno-error=implicit-function-declaration
QMAKE_CXXFLAGS_MOC += -Wno-error=implicit-function-declaration

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
