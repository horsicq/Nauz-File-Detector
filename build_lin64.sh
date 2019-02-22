#!/bin/bash -x
QT_PATH=$HOME/Qt5.6.3/5.6.3/gcc_64
RELEASE_VERSION=$(cat "release_version.txt")
echo $RELEASE_VERSION
SOURCE_PATH=$PWD

BUILD_NAME=nfd_lin64_portable
GUIEXE=nfd
CONEXE=nfdc

cd $SOURCE_PATH

function makeproject
{
    cd $SOURCE_PATH/$1
    
    $QT_PATH/bin/qmake $1.pro -spec linux-g++
    make -f Makefile clean
    make -f Makefile

    rm -rf Makefile
    rm -rf Makefile.Release
    rm -rf Makefile.Debug
    rm -rf object_script.*     

    cd $SOURCE_PATH
}

rm -rf $SOURCE_PATH/build

makeproject gui_source
makeproject console_source

mkdir -p release
rm -rf release/$BUILD_NAME
mkdir -p release/$BUILD_NAME
mkdir -p release/$BUILD_NAME/base
mkdir -p release/$BUILD_NAME/base/platforms

cp -R $QT_PATH/plugins/platforms/libqxcb.so                     $SOURCE_PATH/release/$BUILD_NAME/base/platforms/

cp -R $SOURCE_PATH/build/release/nfd                           $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $SOURCE_PATH/build/release/nfdc                          $SOURCE_PATH/release/$BUILD_NAME/base/

cp -R $QT_PATH/lib/libQt5Core.so.5.6.3                          $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5Gui.so.5.6.3                           $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5Widgets.so.5.6.3                       $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5DBus.so.5.6.3                          $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libQt5XcbQpa.so.5.6.3                        $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libicui18n.so.56.1                           $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libicuuc.so.56.1                             $SOURCE_PATH/release/$BUILD_NAME/base/
cp -R $QT_PATH/lib/libicudata.so.56.1                           $SOURCE_PATH/release/$BUILD_NAME/base/

mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Core.so.5.6.3                $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Core.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Gui.so.5.6.3                 $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Gui.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Widgets.so.5.6.3             $SOURCE_PATH/release/$BUILD_NAME/base/libQt5Widgets.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5DBus.so.5.6.3                $SOURCE_PATH/release/$BUILD_NAME/base/libQt5DBus.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libQt5XcbQpa.so.5.6.3              $SOURCE_PATH/release/$BUILD_NAME/base/libQt5XcbQpa.so.5
mv $SOURCE_PATH/release/$BUILD_NAME/base/libicui18n.so.56.1                 $SOURCE_PATH/release/$BUILD_NAME/base/libicui18n.so.56
mv $SOURCE_PATH/release/$BUILD_NAME/base/libicuuc.so.56.1                   $SOURCE_PATH/release/$BUILD_NAME/base/libicuuc.so.56
mv $SOURCE_PATH/release/$BUILD_NAME/base/libicudata.so.56.1                 $SOURCE_PATH/release/$BUILD_NAME/base/libicudata.so.56

echo "#!/bin/sh" >> release/$BUILD_NAME/nfd.sh
echo "export LD_LIBRARY_PATH=\"./base:$LD_LIBRARY_PATH\"" >> release/$BUILD_NAME/nfd.sh
echo "./base/nfd $*" >> release/$BUILD_NAME/nfd.sh

echo "#!/bin/sh" >> release/$BUILD_NAME/nfdc.sh
echo "export LD_LIBRARY_PATH=\"./base:$LD_LIBRARY_PATH\"" >> release/$BUILD_NAME/nfdc.sh
echo "./base/nfdc $*" >> release/$BUILD_NAME/nfdc.sh

chmod +x release/$BUILD_NAME/nfd.sh
chmod +x release/$BUILD_NAME/nfdc.sh

rm -rf $SOURCE_PATH/release/${BUILD_NAME}_${RELEASE_VERSION}.tar.gz
rm -rf $SOURCE_PATH/release/${BUILD_NAME}_${RELEASE_VERSION}.tar

cd release

tar -cvf ${BUILD_NAME}_${RELEASE_VERSION}.tar $BUILD_NAME
gzip --best ${BUILD_NAME}_${RELEASE_VERSION}.tar

cd ..

rm -rf release/$BUILD_NAME
