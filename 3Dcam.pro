QT += qml quick

CONFIG += c++14

SOURCES += main.cpp \
    gcodegenerator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    gcodegenerator.h
