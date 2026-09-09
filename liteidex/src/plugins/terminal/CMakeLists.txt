set(TGT terminal)

set(SOURCES
    terminalplugin.cpp
    terminal.cpp
    terminaloption.cpp
    terminaloptionfactory.cpp
)

set(HEADERS
    terminalplugin.h
    terminal.h
    terminal_global.h
    terminaloption.h
    terminaloptionfactory.h
)

set(FORMS
    terminaloption.ui
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_compile_definitions(${TGT} PRIVATE
    TERMINAL_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    liteapi
    terminalapi
    libvterm
    tabwidget
    vtermwidget
    ptyqt
)

if(WIN32)
    target_link_libraries(${TGT} PRIVATE
        Qt${QT_VERSION_MAJOR}::Network
        ${QT5_COMPAT_LIB}
    )
endif()