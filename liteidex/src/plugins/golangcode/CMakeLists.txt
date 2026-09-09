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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    liteenvapi
    golangastapi
    fileutil
    processex
    qtc_editutil
)