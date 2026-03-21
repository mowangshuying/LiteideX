set(TGT golangpresent)

set(SOURCES
    golangpresentedit.cpp
    golangpresentplugin.cpp
    exportdialog.cpp
)

set(HEADERS
    golangpresent_global.h
    golangpresentedit.h
    golangpresentplugin.h
    exportdialog.h
)

set(FORMS
    exportdialog.ui
)

set(RESOURCES
    golangpresent.qrc
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    GOLANGPRESENT_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    editorutil
    fileutil
    processex
    liteapi
)