cmake_minimum_required(VERSION 3.16)

include(GNUInstallDirs)

project(nfdc VERSION ${X_PROJECT_VERSION} LANGUAGES CXX)

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

include(${PROJECT_SOURCE_DIR}/../../../_mylibs/SpecAbstract/specabstract.cmake)

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
elseif(APPLE)
else()
    install (TARGETS nfdc DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
