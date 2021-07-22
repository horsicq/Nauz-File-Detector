#!/bin/sh -x
export QMAKE_PATH=$HOME/Qt/5.15.2/clang_64/bin/qmake

export X_SOURCE_PATH=$PWD
export X_BUILD_NAME=nfd_mac_portable
export X_RELEASE_VERSION=$(cat "release_version.txt")

source build_tools/mac.sh

check_file $QMAKE_PATH

if [ -z "$X_ERROR" ]; then
    make_init
    make_build "$X_SOURCE_PATH/NFD_source.pro"

    check_file "$X_SOURCE_PATH/build/release/nfd.app/Contents/MacOS/nfd"
    if [ -z "$X_ERROR" ]; then
        cp -R "$X_SOURCE_PATH/build/release/nfd.app"    "$X_SOURCE_PATH/release/$X_BUILD_NAME"

        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/nfd.app/Contents/Resources/signatures

        fiximport "$X_SOURCE_PATH/build/release/nfd.app/Contents/MacOS/nfd"

        deploy_qt_library QtWidgets nfd
        deploy_qt_library QtGui nfd
        deploy_qt_library QtCore nfd
        deploy_qt_library QtDBus nfd
        deploy_qt_library QtPrintSupport nfd

        deploy_qt_plugin platforms libqcocoa nfd
        deploy_qt_plugin platforms libqminimal nfd
        deploy_qt_plugin platforms libqoffscreen nfd

        make_release
        make_clear
    fi
fi