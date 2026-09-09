set(TGT rustedit)

set(SOURCES
    rusteditplugin.cpp
    rustedit.cpp
)

set(HEADERS
    rusteditplugin.h
    rustedit_global.h
    rustedit.h
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    RUSTEDIT_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    fileutil
    liteenvapi
)