[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=NF3FBD3KHMXDN)
[![GitHub tag (latest SemVer)](https://img.shields.io/github/tag/horsicq/Nauz-File-Detector.svg)](https://github.com/horsicq/Nauz-File-Detector/releases)
[![GitHub All Releases](https://img.shields.io/github/downloads/horsicq/Nauz-File-Detector/total.svg)](https://github.com/horsicq/Nauz-File-Detector/releases)

![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/mascots/0.06.png "Version")

**Nauz File Detector** is a portable linker/compiler/packer identifier utility.

The program works on OSX, Linux and Windows.

There are two versions of  program:

**nfd** - GUI version
**nfdc** - console version.

![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/docs/1.png "1")
![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/docs/2.png "2")

How to run portable version on Linux
=======

- download an appImage file (https://github.com/horsicq/Nauz-File-Detector/releases/download/0.06/NauzFileDetector-0.06-x86_64.AppImage)
- make the file executable (chmod +x NauzFileDetector-0.06-x86_64.AppImage)
- run it (./NauzFileDetector-0.06-x86_64.AppImage)

How to build on Docker
=======
git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

docker build .

How to build on Linux(Debian package, tested on Ubuntu 14.04-20.04)
=======

Install packages:

- sudo apt-get install --quiet --assume-yes git
- sudo apt-get install --quiet --assume-yes build-essential
- sudo apt-get install --quiet --assume-yes qt5-default qtbase5-dev qttools5-dev-tools

git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

Run build script: bash -x build_dpkg.sh

Install deb package: sudo dpkg -i release/nfd_[Version].deb

Run: *nfd [FileName]* or *nfdc [FileName]*

How to build on Linux(Automake)
=======

Qt framework has to be installed on the system.

- (Ubuntu) Install GIT: sudo apt-get install --quiet --assume-yes git
- (Ubuntu 20.04)Install Qt Framework: sudo apt-get install --quiet --assume-yes build-essential qt5-default qtbase5-dev qttools5-dev-tools

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

- chmod a+x configure
- ./configure
- make
- sudo make install

Run: *nfd [FileName]* or *nfdc [FileName]*

How to build on OSX
=======

Install Qt 5.15.2: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

Edit build_mac.bat ( check QT_PATH variable)

Run build_mac.bat

How to build on Windows(XP)
=======

Install Visual Studio 2013: https://github.com/horsicq/build_tools

Install Qt 5.6.3 for VS2013: https://github.com/horsicq/build_tools

Install 7-Zip: https://www.7-zip.org/

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

Edit build_winxp.bat ( check VS_PATH,  SEVENZIP_PATH, QT_PATH variables)

Run build_winxp.bat

How to build on Windows(7-10)
=======

Install Visual Studio 2019: https://github.com/horsicq/build_tools

Install Qt 5.15.2 for VS2019: https://github.com/horsicq/build_tools

Install 7-Zip: https://www.7-zip.org/

Install Inno Setup: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

Edit build_msvc_win32.bat ( check VSVARS_PATH, SEVENZIP_PATH, INNOSETUP_PATH, QMAKE_PATH variables)

Edit build_msvc_win64.bat ( check VSVARS_PATH, SEVENZIP_PATH, INNOSETUP_PATH, QMAKE_PATH variables)

Run build_win32.bat

Run build_win64.bat

![alt text](https://github.com/horsicq/Nauz-File-Detector/blob/master/mascots/nfd.png "Mascot")


