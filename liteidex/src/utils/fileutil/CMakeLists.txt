#cmake_minimum_required(VERSION 3.10)

# Set target name
set(TGT fileutil)

# Common source files
set(COMMON_SOURCES
    fileutil.cpp
    findfilesthread.cpp
)

set(COMMON_HEADERS
    fileutil.h
    findfilesthread.h
)

# Platform-specific sources
if(APPLE)
    list(APPEND COMMON_SOURCES
        fileutil_mac.mm
    )
endif()

# Create static library
add_library(${TGT} STATIC
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
)

target_compile_definitions(${TGT} PRIVATE
    UNICODE
)

# Set header include paths
target_include_directories(${TGT} PUBLIC
   ./
   ../
)

# Link dependencies (no find_package)
#target_link_libraries(${TGT} PRIVATE
#    Qt5::Core
#    liteapi
#)

if(WIN32)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    liteapi
    ole32
    shell32
)
else()
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    liteapi
)

endif()