How to build on Docker
=======
git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

docker build .

How to build on Linux based on Debian
=======

Install packages:

- sudo apt-get install --quiet --assume-yes git
- sudo apt-get install --quiet --assume-yes build-essential
- sudo apt-get install --quiet --assume-yes qtbase5-dev
- sudo apt-get install --quiet --assume-yes qttools5-dev-tools
- sudo apt-get install --quiet --assume-yes qt5-default (Ubuntu 14.04-20.04)
- sudo apt-get install --quiet --assume-yes qt5-qmake (Ubuntu 21.04-22.04)

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

How to build on macOS
=======

Install Qt 5.15.2: https://github.com/horsicq/build_tools

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

Edit build_mac.sh ( check QT_PATH variable)

Run build_mac.sh

How to build on Windows(XP)
=======

Install Visual Studio 2013: https://github.com/horsicq/build_tools

Install Qt 5.6.3 for VS2013: https://github.com/horsicq/build_tools

Install 7-Zip: https://www.7-zip.org/

Clone project: git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git

cd Nauz-File-Detector

Edit build_winxp.bat ( check VS_PATH,  SEVENZIP_PATH, QT_PATH variables)

Run build_winxp.bat

How to build on Windows(7-11)
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
