QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nfd
TEMPLATE = app

include(../build.pri)

SOURCES +=\
        guimainwindow.cpp \
    dialogabout.cpp \
    main_gui.cpp

HEADERS  += guimainwindow.h \
    ../global.h \
    dialogabout.h

FORMS    += guimainwindow.ui \
    dialogabout.ui


!contains(XCONFIG, dialogstaticscan) {
    XCONFIG += dialogstaticscan
    include(../StaticScan/dialogstaticscan.pri)
}

win32 {
    RC_ICONS = ../icons/main.ico
}

macx {
    ICON = ../icons/main.icns
}

RESOURCES += \
    resources.qrc

