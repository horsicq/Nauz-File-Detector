cmake_minimum_required(VERSION 3.16)

project(nfdc VERSION ${X_PROJECT_VERSION} LANGUAGES CXX)

include(../../dep/build_tools/cmake/cpp_standart_setup.cmake)

add_definitions(-DUSE_DEX)
add_definitions(-DUSE_PDF)
add_definitions(-DUSE_ARCHIVE)

if(WIN32)
    add_definitions(-DNOMINMAX)
endif()

include(${PROJECT_SOURCE_DIR}/../../dep/SpecAbstract/specabstract.cmake)

set(PROJECT_SOURCES
    ${SPECABSTRACT_SOURCES}
    main_console.cpp
)

if(WIN32)
    add_executable(nfdc WIN32
        ${PROJECT_SOURCES}
        ${QM_FILES}
        ../../res/resource.rc
    )
else()
    add_executable(nfdc
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
endif()

target_link_libraries(nfdc PRIVATE bzip2)
target_link_libraries(nfdc PRIVATE lzma)
target_link_libraries(nfdc PRIVATE zlib)
target_link_libraries(nfdc PRIVATE capstone)

target_link_libraries(nfdc PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(nfdc PRIVATE Qt${QT_VERSION_MAJOR}::Concurrent)

find_package(Threads REQUIRED)
target_link_libraries(nfdc PRIVATE Threads::Threads)

if(WIN32)
    install (TARGETS nfdc DESTINATION "./")
    include(../../dep/build_tools/cmake/deploy_qt_windows.cmake)
    include(../../dep/build_tools/cmake/deploy_msvc.cmake)
elseif(APPLE)
else()
    install (TARGETS nfdc DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
