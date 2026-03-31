set(TGT helloliteide)

set(SOURCES
    helloliteideplugin.cpp
)

set(HEADERS
    helloliteideplugin.h
    helloliteide_global.h
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    HELLOLITEIDE_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteapi
)