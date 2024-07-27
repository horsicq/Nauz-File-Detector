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

!contains(XCONFIG, specabstract) {
    XCONFIG += specabstract
    include(../SpecAbstract/specabstract.pri)
}

!contains(XCONFIG, xoptions) {
    XCONFIG += xoptions
    include(../XOptions/xoptions.pri)
}

win32 {
    VERSION = 0.10.0.0
    QMAKE_TARGET_COMPANY = NTInfo
    QMAKE_TARGET_PRODUCT = Nauz File Detector
    QMAKE_TARGET_DESCRIPTION = Nauz File Detector(NFD) is a linker/compiler/packer identifier utility.
    QMAKE_TARGET_COPYRIGHT = horsicq@gmail.com
}

DISTFILES += \
    CMakeLists.txt
