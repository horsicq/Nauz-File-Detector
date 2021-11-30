#!/bin/bash -x
export QMAKE_PATH=/usr/bin/qmake

export X_SOURCE_PATH=$PWD
export X_BUILD_NAME=nfd_linux_portable
export X_RELEASE_VERSION=$(cat "release_version.txt")

source build_tools/linux.sh

check_file $QMAKE_PATH

if [ -z "$X_ERROR" ]; then
    make_init
    make_build "$X_SOURCE_PATH/NFD_source.pro"

    check_file "$X_SOURCE_PATH/build/release/nfd"
    check_file "$X_SOURCE_PATH/build/release/nfdc"
    if [ -z "$X_ERROR" ]; then
        create_deb_app_dir nfd
        
        #cp -f $X_SOURCE_PATH/LICENSE                                        $X_SOURCE_PATH/release/$X_BUILD_NAME/
        cp -f $X_SOURCE_PATH/LINUX/control                                  $X_SOURCE_PATH/release/$X_BUILD_NAME/LINUX/
        sed -i "s/#VERSION#/$X_RELEASE_VERSION/"                            $X_SOURCE_PATH/release/$X_BUILD_NAME/LINUX/control
        sed -i "s/#ARCH#/$X_ARCHITECTURE/"                                  $X_SOURCE_PATH/release/$X_BUILD_NAME/LINUX/control
        cp -f $X_SOURCE_PATH/build/release/nfd                              $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/bin/
        cp -f $X_SOURCE_PATH/build/release/nfdc                             $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/bin/
        cp -f $X_SOURCE_PATH/LINUX/nfd.desktop                              $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/share/applications/
        sed -i "s/#VERSION#/$X_RELEASE_VERSION/"                            $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/share/applications/nfd.desktop
        cp -Rf $X_SOURCE_PATH/LINUX/hicolor/                                $X_SOURCE_PATH/release/$X_BUILD_NAME/usr/share/icons/

        make_deb
        #mv $X_SOURCE_PATH/release/$X_BUILD_NAME.deb $X_SOURCE_PATH/release/nfd_${X_RELEASE_VERSION}-${X_REVISION}_${X_OS_VERSION}_${X_ARCHITECTURE}.deb
        mv $X_SOURCE_PATH/release/$X_BUILD_NAME.deb $X_SOURCE_PATH/release/nfd_${X_RELEASE_VERSION}_${X_OS_VERSION}_${X_ARCHITECTURE}.deb
        make_clear
    fi
fi
