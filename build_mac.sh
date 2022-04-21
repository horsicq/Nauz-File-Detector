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

    check_file "$X_SOURCE_PATH/build/release/NFD.app/Contents/MacOS/NFD"
    if [ -z "$X_ERROR" ]; then
        cp -R "$X_SOURCE_PATH/build/release/NFD.app"    "$X_SOURCE_PATH/release/$X_BUILD_NAME"

        mkdir -p $X_SOURCE_PATH/release/$X_BUILD_NAME/NFD.app/Contents/Resources/signatures
        cp -Rf $X_SOURCE_PATH/XStyles/qss                    $X_SOURCE_PATH/release/$X_BUILD_NAME/NFD.app/Contents/Resources/

        fiximport "$X_SOURCE_PATH/build/release/NFD.app/Contents/MacOS/NFD"

        deploy_qt_library QtWidgets NFD
        deploy_qt_library QtGui NFD
        deploy_qt_library QtCore NFD
        deploy_qt_library QtDBus NFD
        deploy_qt_library QtPrintSupport NFD

        deploy_qt_plugin platforms libqcocoa NFD
        deploy_qt_plugin platforms libqminimal NFD
        deploy_qt_plugin platforms libqoffscreen NFD

        make_release
        make_clear
    fi
fi