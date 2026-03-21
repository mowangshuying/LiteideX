set(TGT litetty)

set(SOURCES
    litettyplugin.cpp
    litetty.cpp
    sockettty.cpp
)

set(HEADERS
    litettyplugin.h
    litetty_global.h
    litetty.h
    sockettty.h
)

if(UNIX AND NOT APPLE AND NOT WIN32)
    list(APPEND SOURCES
        fifotty.cpp
    )
    list(APPEND HEADERS
        fifotty.h
    )
endif()

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    LITETTY_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    liteapi
    litettyapi
)