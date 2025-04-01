cmake_minimum_required(VERSION 3.16)

project(NauzFileDetector VERSION ${X_PROJECT_VERSION} LANGUAGES CXX)

include(../../dep/build_tools/cmake/cpp_standart_setup.cmake)

set(X_RESOURCES ${CMAKE_INSTALL_LIBDIR}/NauzFileDetector)

add_definitions(-DUSE_DEX)
add_definitions(-DUSE_PDF)
add_definitions(-DUSE_ARCHIVE)

if(WIN32)
    add_definitions(-DNOMINMAX)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
include(../../dep/build_tools/cmake/init_translation.cmake)
endif()

include(${PROJECT_SOURCE_DIR}/../../dep/nfd_widget/nfd_widget.cmake)
include(${PROJECT_SOURCE_DIR}/../../dep/XOptions/xoptionswidget.cmake)
include(${PROJECT_SOURCE_DIR}/../../dep/XAboutWidget/xaboutwidget.cmake)
include(${PROJECT_SOURCE_DIR}/../../dep/XStyles/xstyles.cmake)

set(PROJECT_SOURCES
    ${NFD_WIDGET_SOURCES}
    ${XOPTIONSWIDGET_SOURCES}
    ${XABOUTWIDGET_SOURCES}
    dialogabout.cpp
    dialogabout.ui
    dialogoptions.cpp
    dialogoptions.ui
    guimainwindow.cpp
    guimainwindow.ui
    main_gui.cpp
    resources.qrc
)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
include(../../dep/build_tools/cmake/create_translation.cmake)
endif()

if(WIN32)
    add_executable(NauzFileDetector WIN32
        ${PROJECT_SOURCES}
        ${QM_FILES}
        ../../res/resource_icon.rc
    )
elseif(APPLE)
    add_executable(NauzFileDetector
        MACOSX_BUNDLE
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
else()
    add_executable(NauzFileDetector
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
endif()

set_target_properties(NauzFileDetector PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(APPLE)
    include(../../dep/build_tools/cmake/macdeployqt.cmake)
endif()

target_link_libraries(NauzFileDetector PRIVATE bzip2)
target_link_libraries(NauzFileDetector PRIVATE lzma)
target_link_libraries(NauzFileDetector PRIVATE zlib)
target_link_libraries(NauzFileDetector PRIVATE capstone)

target_link_libraries(NauzFileDetector PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(NauzFileDetector PRIVATE Qt${QT_VERSION_MAJOR}::Concurrent)
target_link_libraries(NauzFileDetector PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(NauzFileDetector PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(NauzFileDetector PRIVATE Qt${QT_VERSION_MAJOR}::Svg)

find_package(Threads REQUIRED)
target_link_libraries(NauzFileDetector PRIVATE Threads::Threads)

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")

if(WIN32)
    install (TARGETS NauzFileDetector DESTINATION "./")
    include(../../dep/build_tools/cmake/deploy_qt_windows.cmake)
    include(../../dep/build_tools/cmake/deploy_msvc.cmake)
    include(../../dep/build_tools/cmake/deploy_openssl.cmake)
elseif(APPLE)
    install(TARGETS NauzFileDetector
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install (TARGETS NauzFileDetector DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
