set(TGT liteenv)

set(SOURCES
    liteenvplugin.cpp
    envmanager.cpp
    liteenvoptionfactory.cpp
    liteenvoption.cpp
    goenvmanager.cpp
)

set(HEADERS
    liteenvplugin.h
    liteenv_global.h
    envmanager.h
    liteenvoptionfactory.h
    liteenvoption.h
    goenvmanager.h
)

set(FORMS
    liteenvoption.ui
)

set(RESOURCES
    liteenv.qrc
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
    LITEENV_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteenvapi
    fileutil
    processex
)