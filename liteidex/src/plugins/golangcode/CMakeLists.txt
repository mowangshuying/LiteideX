set(TGT golangcode)

set(SOURCES
    golangcodeplugin.cpp
    golangcode.cpp
    golangcodeoptionfactory.cpp
    golangcodeoption.cpp
    ../liteeditor/faketooltip.cpp
)

set(HEADERS
    golangcodeplugin.h
    golangcode_global.h
    golangcode.h
    golangcodeoptionfactory.h
    golangcodeoption.h
    ../liteeditor/faketooltip.h
)

set(FORMS
    golangcodeoption.ui
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_include_directories(${TGT} PUBLIC
    ./
    ../liteeditor
)

target_compile_definitions(${TGT} PRIVATE
    GOLANGCODE_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteenvapi
    golangastapi
    fileutil
    processex
    qtc_editutil
)