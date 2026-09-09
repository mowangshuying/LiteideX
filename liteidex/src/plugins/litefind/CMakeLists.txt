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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    litefindapi
    textoutput
    qtc_searchresult
)