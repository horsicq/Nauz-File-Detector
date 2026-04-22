include(../../dep/build_tools/cmake/cpp_standart_setup.cmake)

add_definitions(-DUSE_DEX)
add_definitions(-DUSE_PDF)
add_definitions(-DUSE_ARCHIVE)
add_definitions(-DUSE_XSIMD)

include(${CMAKE_CURRENT_LIST_DIR}/../../dep/nfd_widget/nfd_widget.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/XOptions/xoptionswidget.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/XAboutWidget/xaboutwidget.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/XStyles/xstyles.cmake)

find_package(Threads REQUIRED)

set(NFD_GUI_TARGET NauzFileDetector)
set(NFD_GUI_SOURCES
    ${NFD_WIDGET_SOURCES}
    ${XOPTIONSWIDGET_SOURCES}
    ${XABOUTWIDGET_SOURCES}
    ${XSTYLES_SOURCES}
    dialogabout.cpp
    dialogabout.h
    dialogabout.ui
    dialogoptions.cpp
    dialogoptions.h
    dialogoptions.ui
    guimainwindow.cpp
    guimainwindow.h
    guimainwindow.ui
    main_gui.cpp
    resources.qrc
)

if(WIN32 AND EXISTS "${X_WINDOWS_RESOURCE_ICON_RC}")
    list(APPEND NFD_GUI_SOURCES "${X_WINDOWS_RESOURCE_ICON_RC}")
endif()

if(APPLE AND EXISTS "${X_MACOS_ICON}")
    set_source_files_properties("${X_MACOS_ICON}" PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    list(APPEND NFD_GUI_SOURCES "${X_MACOS_ICON}")
endif()

add_executable(${NFD_GUI_TARGET} WIN32
    ${NFD_GUI_SOURCES}
)

set_target_properties(${NFD_GUI_TARGET} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "${MACOSX_BUNDLE_GUI_IDENTIFIER}"
    OUTPUT_NAME "${X_ORIGINAL_FILENAME}"
)

target_include_directories(${NFD_GUI_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${NFD_GUI_TARGET} PRIVATE
    bzip2
    lzma
    zlib
    ppmd
    capstone
    xsimd
    Qt${NFD_QT_MAJOR}::Widgets
    Qt${NFD_QT_MAJOR}::Concurrent
    Qt${NFD_QT_MAJOR}::PrintSupport
    Qt${NFD_QT_MAJOR}::OpenGL
    Qt${NFD_QT_MAJOR}::Svg
    Threads::Threads
)

if(WIN32)
    target_link_libraries(${NFD_GUI_TARGET} PRIVATE Wintrust Crypt32)
endif()

if(TARGET nfd_translations)
    add_dependencies(${NFD_GUI_TARGET} nfd_translations)
endif()

if(UNIX AND NOT APPLE)
    set(NFD_RUNTIME_DESTINATION "${CMAKE_INSTALL_BINDIR}")
    set(NFD_DOC_DESTINATION "${CMAKE_INSTALL_DOCDIR}/nauzfiledetector")
    set(NFD_DESKTOP_TEMPLATE "${CMAKE_CURRENT_SOURCE_DIR}/../../res/linux/nfd.desktop.in")
    set(NFD_DESKTOP_FILE "${CMAKE_CURRENT_BINARY_DIR}/nfd.desktop")

    if(EXISTS "${NFD_DESKTOP_TEMPLATE}")
        configure_file("${NFD_DESKTOP_TEMPLATE}" "${NFD_DESKTOP_FILE}" @ONLY)
    endif()
else()
    set(NFD_RUNTIME_DESTINATION ".")
    set(NFD_DOC_DESTINATION ".")
endif()

install(TARGETS ${NFD_GUI_TARGET}
    RUNTIME DESTINATION ${NFD_RUNTIME_DESTINATION}
    BUNDLE DESTINATION .
)

if(UNIX AND NOT APPLE)
    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../README.md"
        DESTINATION ${NFD_DOC_DESTINATION}
        OPTIONAL
    )

    if(EXISTS "${NFD_DESKTOP_FILE}")
        install(FILES "${NFD_DESKTOP_FILE}"
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications")
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../res/linux/hicolor")
        install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../res/linux/hicolor/"
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor")
    endif()
else()
    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE"
        DESTINATION .
        RENAME LICENSE.txt
        OPTIONAL
    )

    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../README.md"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../res/license.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../res/readme.txt"
        "${X_WINDOWS_ICON}"
        DESTINATION .
        OPTIONAL
    )

    install(CODE [[file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/portable" "")]])
endif()

if(APPLE)
    include(${CMAKE_CURRENT_LIST_DIR}/../../dep/build_tools/cmake/macdeployqt.cmake)
endif()

if(WIN32)
    include(${CMAKE_CURRENT_LIST_DIR}/../../dep/build_tools/cmake/deploy_qt_windows.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/../../dep/build_tools/cmake/deploy_msvc.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/../../dep/build_tools/cmake/deploy_openssl.cmake)
endif()
