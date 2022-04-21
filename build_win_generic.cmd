call %X_SOURCE_PATH%\build_tools\windows.cmd make_init

IF NOT [%X_ERROR%] == [] goto exit

call %X_SOURCE_PATH%\build_tools\windows.cmd make_build %X_SOURCE_PATH%\NFD_source.pro

cd %X_SOURCE_PATH%\gui_source
call %X_SOURCE_PATH%\build_tools\windows.cmd make_translate gui_source_tr.pro 
cd %X_SOURCE_PATH%

call %X_SOURCE_PATH%\build_tools\windows.cmd check_file %X_SOURCE_PATH%\build\release\nfd.exe

IF NOT [%X_ERROR%] == [] goto exit

call %X_SOURCE_PATH%\build_tools\windows.cmd check_file %X_SOURCE_PATH%\build\release\nfdc.exe

IF NOT [%X_ERROR%] == [] goto exit

copy %X_SOURCE_PATH%\build\release\nfd.exe %X_SOURCE_PATH%\release\%X_BUILD_NAME%\
copy %X_SOURCE_PATH%\build\release\nfdc.exe %X_SOURCE_PATH%\release\%X_BUILD_NAME%\
xcopy %X_SOURCE_PATH%\XStyles\qss %X_SOURCE_PATH%\release\%X_BUILD_NAME%\qss /E /I

call %X_SOURCE_PATH%\build_tools\windows.cmd deploy_qt_library Qt5Widgets
call %X_SOURCE_PATH%\build_tools\windows.cmd deploy_qt_library Qt5Gui
call %X_SOURCE_PATH%\build_tools\windows.cmd deploy_qt_library Qt5Core
call %X_SOURCE_PATH%\build_tools\windows.cmd deploy_qt_plugin platforms qwindows
call %X_SOURCE_PATH%\build_tools\windows.cmd deploy_redist

call %X_SOURCE_PATH%\build_tools\windows.cmd make_release
:exit
call %X_SOURCE_PATH%\build_tools\windows.cmd make_clear