cmake_minimum_required(VERSION 3.16)

include(GNUInstallDirs)

project(nfd VERSION ${X_PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /MANIFEST:NO")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
endif()

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
    add_executable(nfd WIN32
        ${PROJECT_SOURCES}
        ${QM_FILES}
        ../../res/resource.rc
    )
else()
    add_executable(nfd
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
endif()

set_target_properties(nfd PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(nfd PRIVATE bzip2)
target_link_libraries(nfd PRIVATE lzma)
target_link_libraries(nfd PRIVATE zlib)
target_link_libraries(nfd PRIVATE capstone)

target_link_libraries(nfd PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(nfd PRIVATE Qt${QT_VERSION_MAJOR}::Concurrent)
target_link_libraries(nfd PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(nfd PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(nfd PRIVATE Qt${QT_VERSION_MAJOR}::Svg)

find_package(Threads REQUIRED)
target_link_libraries(nfd PRIVATE Threads::Threads)

if(WIN32)
    install (TARGETS nfd DESTINATION "./")
    install (DIRECTORY ../../dep/XStyles/qss DESTINATION "./" OPTIONAL)
    install (FILES ${QM_FILES} DESTINATION "./lang" OPTIONAL)
    include(../../dep/build_tools/cmake/deploy_qt_windows.cmake)
    include(../../dep/build_tools/cmake/deploy_msvc.cmake)
    include(../../dep/build_tools/cmake/deploy_openssl.cmake)
elseif(APPLE)
    install(TARGETS nfd
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install (TARGETS nfd DESTINATION ${CMAKE_INSTALL_BINDIR})
    install (DIRECTORY ../../dep/XStyles/qss DESTINATION ${CMAKE_INSTALL_LIBDIR}/nfd OPTIONAL)
    install (FILES ${QM_FILES} DESTINATION ${CMAKE_INSTALL_LIBDIR}/nfd/lang OPTIONAL)
endif()

# if(${QT_VERSION_MAJOR} EQUAL 6)
#     qt_finalize_executable(xbinaryviewer)
# endif()
