set(TGT litefind)

set(SOURCES
    litefindplugin.cpp
    filesearch.cpp
    findeditor.cpp
    filesearchmanager.cpp
    replacedocument.cpp
)

set(HEADERS
    litefindplugin.h
    litefind_global.h
    filesearch.h
    findeditor.h
    filesearchmanager.h
    replacedocument.h
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    LITEFIND_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    litefindapi
    textoutput
    qtc_searchresult
)