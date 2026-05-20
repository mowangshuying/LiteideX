set(TGT golangpls)

set(SOURCES
    golangplsplugin.cpp
    golangpls.cpp
)

set(HEADERS
    golangplsplugin.h
    golangpls_global.h
    golangpls.h
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    GOLANGPLS_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    processex
    qjson
    liteapi
    liteenvapi
)