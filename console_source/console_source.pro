QT += core
QT -= gui

CONFIG += c++11

TARGET = nfdc
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += \
    main_console.cpp

XCONFIG += use_capstone_x86

!contains(XCONFIG, staticscan) {
    XCONFIG += staticscan
    include(../StaticScan/staticscan.pri)
}

win32 {
    CONFIG -= embed_manifest_exe
    QMAKE_MANIFEST = windows.manifest.xml
}

DISTFILES += \
    CMakeLists.txt
