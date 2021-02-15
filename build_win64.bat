set VS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"
set QT_PATH=C:\Qt\5.15.2\msvc2019
set SEVENZIP_PATH="C:\Program Files\7-Zip"

set BUILD_NAME=nfd_win64_portable
set SOURCE_PATH=%~dp0
mkdir %SOURCE_PATH%\build
mkdir %SOURCE_PATH%\release
set /p RELEASE_VERSION=<%SOURCE_PATH%\release_version.txt

set QT_PATH=%QT_PATH%
call %VS_PATH%\VC\Auxiliary\Build\vcvars64.bat
set GUIEXE=nfd.exe
set CONEXE=nfdc.exe
set ZIP_NAME=%BUILD_NAME%_%RELEASE_VERSION%
set RES_FILE=rsrc

cd build_libs
%QT_PATH%\bin\qmake.exe build_libs.pro -r -spec win32-msvc "CONFIG+=release"

nmake Makefile.Release clean
nmake
del Makefile
del Makefile.Release
del Makefile.Debug

cd ..

cd gui_source
%QT_PATH%\bin\qmake.exe gui_source.pro -r -spec win32-msvc "CONFIG+=release"

nmake Makefile.Release clean
nmake
del Makefile
del Makefile.Release
del Makefile.Debug

cd ..

cd console_source
%QT_PATH%\bin\qmake.exe console_source.pro -r -spec win32-msvc "CONFIG+=release"

nmake Makefile.Release clean
nmake
del Makefile
del Makefile.Release
del Makefile.Debug

cd ..

mkdir %SOURCE_PATH%\release\%BUILD_NAME%
mkdir %SOURCE_PATH%\release\%BUILD_NAME%\platforms

copy %SOURCE_PATH%\build\release\%GUIEXE% %SOURCE_PATH%\release\%BUILD_NAME%\
copy %SOURCE_PATH%\build\release\%CONEXE% %SOURCE_PATH%\release\%BUILD_NAME%\
copy %QT_PATH%\bin\Qt5Widgets.dll %SOURCE_PATH%\release\%BUILD_NAME%\
copy %QT_PATH%\bin\Qt5Gui.dll %SOURCE_PATH%\release\%BUILD_NAME%\
copy %QT_PATH%\bin\Qt5Core.dll %SOURCE_PATH%\release\%BUILD_NAME%\
copy %QT_PATH%\plugins\platforms\qwindows.dll %SOURCE_PATH%\release\%BUILD_NAME%\platforms\

copy %VS_PATH%\VC\Redist\MSVC\14.27.29016\x64\Microsoft.VC142.CRT\msvcp140.dll %SOURCE_PATH%\release\%BUILD_NAME%\
copy %VS_PATH%\VC\Redist\MSVC\14.27.29016\x64\Microsoft.VC142.CRT\vcruntime140.dll %SOURCE_PATH%\release\%BUILD_NAME%\
copy %VS_PATH%\VC\Redist\MSVC\14.27.29016\x64\Microsoft.VC142.CRT\msvcp140_1.dll %SOURCE_PATH%\release\%BUILD_NAME%\
copy %VS_PATH%\VC\Redist\MSVC\14.27.29016\x64\Microsoft.VC142.CRT\vcruntime140_1.dll %SOURCE_PATH%\release\%BUILD_NAME%\

cd %SOURCE_PATH%\release
if exist %ZIP_NAME%.zip del %ZIP_NAME%.zip
%SEVENZIP_PATH%\7z.exe a %ZIP_NAME%.zip %BUILD_NAME%\*
rmdir /s /q %SOURCE_PATH%\release\%BUILD_NAME%
cd ..