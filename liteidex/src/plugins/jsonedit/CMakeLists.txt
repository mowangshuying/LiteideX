set(TGT jsonedit)

set(SOURCES
    jsoneditplugin.cpp
    jsonedit.cpp
)

set(HEADERS
    jsoneditplugin.h
    jsonedit_global.h
    jsonedit.h
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    JSONEDIT_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    qjson
    editorutil
    liteapi
)