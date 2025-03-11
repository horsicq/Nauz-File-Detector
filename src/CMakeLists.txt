cmake_minimum_required(VERSION 3.10)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)

if(${QT_VERSION_MAJOR} EQUAL 5)
    if(${QT_VERSION} VERSION_GREATER_EQUAL 5.6.0)
        find_package(Qt5 REQUIRED COMPONENTS Widgets Concurrent Network PrintSupport OpenGL Svg LinguistTools)
    else()
        find_package(Qt5 REQUIRED COMPONENTS Widgets Concurrent Network PrintSupport OpenGL Svg)
    endif()
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Concurrent Network PrintSupport OpenGL Svg LinguistTools)
endif()

file (STRINGS ${PROJECT_SOURCE_DIR}/release_version.txt X_PROJECT_VERSION)
project(NauzFileDetector VERSION ${X_PROJECT_VERSION} LANGUAGES CXX)

set(X_COMPANYNAME "ntinfo")
set(X_PROJECTNAME "NauzFileDetector")
set(X_MAINTAINER "horsicq@gmail.com")
set(X_DESCRIPTION "NFD is a file detector")
set(X_HOMEPAGE "http://ntinfo.biz")
set(X_ORIGINAL_FILENAME "nfd")

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.nfd)
endif()

include(../dep/build_tools/cmake/deploy_init.cmake)

message(STATUS X_PROJECT_ARCH: ${X_PROJECT_ARCH})

add_subdirectory(../dep/XCapstone XCapstone)
add_subdirectory(../dep/XArchive XArchive)
add_subdirectory(gui nfd)
add_subdirectory(cli nfdc)
