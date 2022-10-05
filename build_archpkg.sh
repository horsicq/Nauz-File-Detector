#!/bin/bash -x
mkdir release
cp -f PKGBUILD release/
cd release
makepkg -Acs
rm -Rf PKGBUILD
rm -Rf Nauz-File-Detector
cd ..
