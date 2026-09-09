set(TGT golangfmt)

set(SOURCES
    golangfmtplugin.cpp
    golangfmt.cpp
    golangfmtoptionfactory.cpp
    golangfmtoption.cpp
)

set(HEADERS
    golangfmtplugin.h
    golangfmt_global.h
    golangfmt.h
    golangfmtoptionfactory.h
    golangfmtoption.h
)

set(FORMS
    golangfmtoption.ui
)

set(RESOURCES
    golangfmt.qrc
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
    GOLANGFMT_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    liteenvapi
    fileutil
    processex
    diff_match_patch
)