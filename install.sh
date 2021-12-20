#!/bin/bash -x
export X_SOURCE_PATH=$PWD

cp -f $X_SOURCE_PATH/build/release/nfd                            /usr/bin/
cp -f $X_SOURCE_PATH/build/release/nfdc                            /usr/bin/
cp -f $X_SOURCE_PATH/LINUX/nfd.desktop                           /usr/share/applications/
cp -Rf $X_SOURCE_PATH/LINUX/hicolor/                               /usr/share/icons/
