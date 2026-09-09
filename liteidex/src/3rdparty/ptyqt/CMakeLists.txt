#cmake_minimum_required(VERSION 3.10)

# Set target name
set(TGT ptyqt)

# Common source files
set(COMMON_SOURCES
    core/ptyqt.cpp
)

set(COMMON_HEADERS
    core/iptyprocess.h
    core/ptyqt.h
)

# Platform-specific sources
if(WIN32)
    set(PLATFORM_SOURCES
        ${COMMON_SOURCES}
    )
    
    set(PLATFORM_HEADERS
        ${COMMON_HEADERS}
        core/winpty.h
        core/winpty_constants.h
    )
    
    # MinGW compiler
    if(MINGW)
        list(APPEND PLATFORM_SOURCES
            core/winptyprocess.cpp
        )
        list(APPEND PLATFORM_HEADERS
            core/winptyprocess.h
        )
    endif()
    
    # MSVC compiler
    if(MSVC)
        list(APPEND PLATFORM_SOURCES
            core/conptyprocess.cpp
        )
        list(APPEND PLATFORM_HEADERS
            core/conptyprocess.h
        )
    endif()
    
    # Qt Network module for Windows
    set(QT_COMPONENTS Core Network)
else()
    # Unix/Linux/macOS
    set(PLATFORM_SOURCES
        ${COMMON_SOURCES}
        core/unixptyprocess.cpp
    )
    
    set(PLATFORM_HEADERS
        ${COMMON_HEADERS}
        core/unixptyprocess.h
    )
    
    set(QT_COMPONENTS Core)
endif()

# Create static library
add_library(${TGT} STATIC
    ${PLATFORM_SOURCES}
    ${PLATFORM_HEADERS}
)

# Include common configuration
#include(../../liteideutils.cmake)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
    ./core
)

## define UNICODE
target_compile_definitions(${TGT} PRIVATE
    UNICODE
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
)

# Install configuration (optional)
#install(TARGETS ${TGT}
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)

#install(FILES
#    core/iptyprocess.h
#    core/ptyqt.h
#    DESTINATION include/ptyqt
#)