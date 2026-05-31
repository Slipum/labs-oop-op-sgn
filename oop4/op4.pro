QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += ./src

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./src/main.cpp \
    ./src/business/file.cpp \
    ./src/drawer/drawer.cpp \
    ./src/entities/abstructs/services/figure.cpp \
    ./src/entities/abstructs/services/vertex.cpp \
    ./src/facade.cpp \
    ./src/interface/graphics/visual.cpp \
    ./src/interface/mainwindow.cpp \
    ./src/interface/qtscene.cpp \
    ./src/math/transform.cpp \
    ./src/scene/camera.cpp \
    ./src/scene/scene.cpp

HEADERS += \
    ./src/business/file.h \
    ./src/business/normalization.h \
    ./src/drawer/drawer.h \
    ./src/entities/abstructs/edge.h \
    ./src/entities/abstructs/figure.h \
    ./src/entities/abstructs/vertex.h \
    ./src/entities/object.h \
    ./src/entities/point.h \
    ./src/facade.h \
    ./src/interface/graphics/visual.h \
    ./src/interface/mainwindow.h \
    ./src/interface/qtscene.h \
    ./src/math/transform.h \
    ./src/scene/camera.h \
    ./src/scene/scene.h

FORMS += \
    ./src/interface/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
