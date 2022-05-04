#!/bin/bash -x
export X_SOURCE_PATH=$PWD

if [ -z "$1" ]; then
    X_PREFIX="/usr"
else
    X_PREFIX="$1"
fi

mkdir -p  $X_PREFIX/lib/bin
mkdir -p  $X_PREFIX/lib/share/applications
mkdir -p  $X_PREFIX/lib/share/icons

cp -f $X_SOURCE_PATH/build/release/nfd                              $X_PREFIX/bin/
cp -f $X_SOURCE_PATH/build/release/nfdc                             $X_PREFIX/bin/
cp -f $X_SOURCE_PATH/LINUX/nfd.desktop                              $X_PREFIX/share/applications/
cp -Rf $X_SOURCE_PATH/LINUX/hicolor/                                $X_PREFIX/share/icons/
