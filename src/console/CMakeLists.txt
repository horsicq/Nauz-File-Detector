set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DUSE_XSIMD)

if(WIN32)
    add_definitions(-DNOMINMAX)
endif()

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE)
    add_compile_options(/FS)
    # Older CMake versions (and caches made before CMP0141) put /Zi in
    # these flags. Remove only the debug format in this directory's scope;
    # the console target selects Embedded below. Preserve runtime/optimizer
    # flags and leave sibling targets' flag variables untouched.
    foreach(nfd_debug_config DEBUG RELWITHDEBINFO)
        string(REGEX REPLACE "(^|[ \t])[-/]Z[iI7]([ \t]|$)" "\\1\\2"
            CMAKE_CXX_FLAGS_${nfd_debug_config} "${CMAKE_CXX_FLAGS_${nfd_debug_config}}")
    endforeach()
endif()

include(${CMAKE_CURRENT_LIST_DIR}/../../dep/SpecAbstract/specabstract.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/XScanEngine/xscanengineconsole.cmake)

find_package(Threads REQUIRED)

if(UNIX AND NOT APPLE)
    include(GNUInstallDirs)
endif()

add_executable(nfdc
    ${SPECABSTRACT_SOURCES}
    ${XSCANENGINECONSOLE_SOURCES}
    main_console.cpp
)

if(MSVC)
    if(POLICY CMP0141)
        set_property(TARGET nfdc PROPERTY MSVC_DEBUG_INFORMATION_FORMAT
            "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
    else()
        target_compile_options(nfdc PRIVATE
            "$<$<CONFIG:Debug>:/Z7>" "$<$<CONFIG:RelWithDebInfo>:/Z7>")
    endif()
endif()

target_include_directories(nfdc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(nfdc PRIVATE
    bzip2
    lzma
    zlib
    ppmd
    capstone
    xsimd
    Qt${NFD_QT_MAJOR}::Core
    Qt${NFD_QT_MAJOR}::Concurrent
    Threads::Threads
)

if(WIN32)
    target_link_libraries(nfdc PRIVATE Wintrust Crypt32)
endif()

if(TARGET nfd_translations)
    add_dependencies(nfdc nfd_translations)
endif()

if(UNIX AND NOT APPLE)
    install(TARGETS nfdc RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
else()
    install(TARGETS nfdc RUNTIME DESTINATION ".")
endif()
