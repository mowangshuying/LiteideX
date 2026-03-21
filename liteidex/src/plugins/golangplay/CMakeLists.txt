set(TGT golangplay)

set(SOURCES
    golangplayplugin.cpp
    goplaybrowser.cpp
)

set(HEADERS
    golangplayplugin.h
    golangplay_global.h
    goplaybrowser.h
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    GOLANGPLAY_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    fileutil
    textoutput
    processex
    colorstyle
    liteapi
)