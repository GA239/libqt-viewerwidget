#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T22:14:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewer-example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG(debug, debug|release) {
    LIBS+= -L../build-src-desktop/debug -llibqt-viewerwidget
}

CONFIG(release, debug|release) {
    LIBS+= -L../build-src-desktop/release -llibqt-viewerwidget
}

DISTFILES +=
