[![GitHub tag (latest SemVer)](https://img.shields.io/github/tag/horsicq/Nauz-File-Detector.svg)](https://github.com/horsicq/Nauz-File-Detector/releases)
[![GitHub All Releases](https://img.shields.io/github/downloads/horsicq/Nauz-File-Detector/total.svg)](https://github.com/horsicq/Nauz-File-Detector/releases)

![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/mascots/0.05.jpg "Mascot")

Nauz File Detector is a portable linker/compiler/packer identifier utility.

The program works on OSX, Linux and Windows.
There are two versions of  program.

**nfd** - GUI version
**nfdc** - console version.

![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/screenshot_gui.jpg "Screenshot gui")
![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/screenshot_console.jpg "Screenshot console")

How to build on Docker
=======
git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

Nauz-File-Detector

docker build .

How to build on Linux(Debian package)
=======

Install packages:

- sudo apt-get install qtbase5-dev -y
- sudo apt-get install qttools5-dev-tools -y
- sudo apt-get install git -y
- sudo apt-get install build-essential -y
- sudo apt-get install qt5-default -y

git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

Nauz-File-Detector

Run build script: bash -x build_dpkg.sh

Install deb package: sudo dpkg -i release/nfd_[Version].deb

Run: *nfd [FileName]* or *nfdc [FileName]*

How to build on Linux(Automake)
=======

Qt framework has to be installed on the system.

(Ubuntu)Install Qt Framework: sudo apt-get install --quiet --assume-yes build-essential qt5-default qtbase5-dev qttools5-dev-tools

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

- chmod a+x configure
- ./configure
- make
- sudo make install

Run: *nfd [FileName]* or *nfdc [FileName]*

How to build on OSX
=======

Install Qt 5.15.2: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

Edit build_mac.bat ( check QT_PATH variable)

Run build_mac.bat

How to build on Windows(XP)
=======

Install Visual Studio 2013: https://github.com/horsicq/build_tools

Install Qt 5.6.3 for VS2013: https://github.com/horsicq/build_tools

Install 7-Zip: https://www.7-zip.org/

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

Edit build_winxp.bat ( check VS_PATH,  SEVENZIP_PATH, QT_PATH variables)

Run build_winxp.bat

How to build on Windows(7-10)
=======

Install Visual Studio 2019: https://github.com/horsicq/build_tools

Install Qt 5.15.2 for VS2019: https://github.com/horsicq/build_tools

Install 7-Zip: https://www.7-zip.org/

Install Inno Setup: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

Edit build_msvc_win32.bat ( check VSVARS_PATH, SEVENZIP_PATH, INNOSETUP_PATH, QMAKE_PATH variables)

Edit build_msvc_win64.bat ( check VSVARS_PATH, SEVENZIP_PATH, INNOSETUP_PATH, QMAKE_PATH variables)

Run build_win32.bat

Run build_win64.bat

![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/mascots/nfd.jpg "Mascot")


