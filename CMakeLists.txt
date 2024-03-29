cmake_minimum_required(VERSION 3.10)

project(MainProject)

if(WIN32)
    set (CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019/")
endif()

if(APPLE)
    set (CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.15.2/clang_64/)
    set (CMAKE_OSX_ARCHITECTURES x86_64)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-switch)
endif()

add_subdirectory(XCapstone/x86)
add_subdirectory(XArchive)
add_subdirectory(gui_source)
add_subdirectory(console_source)

include(GNUInstallDirs)

if(WIN32)
    install (TARGETS nfd)
    install (TARGETS nfdc)
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    install (TARGETS nfd LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install (TARGETS nfdc LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install (FILES LINUX/nfd.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications/)
    install (DIRECTORY LINUX/hicolor DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons)
    install (DIRECTORY XStyles/qss DESTINATION ${CMAKE_INSTALL_LIBDIR}/nfd)
    install (DIRECTORY images DESTINATION ${CMAKE_INSTALL_LIBDIR}/nfd)
endif()

if(APPLE)
    install (TARGETS nfd
                BUNDLE DESTINATION .
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install (TARGETS nfdc
                BUNDLE DESTINATION .
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
