set(TGT bookmarks)

set(SOURCES
    bookmarksplugin.cpp
    bookmarkmanager.cpp
    bookmarkmodel.cpp
)

set(HEADERS
    bookmarksplugin.h
    bookmarks_global.h
    bookmarkmanager.h
    bookmarkmodel.h
)

set(RESOURCES
    bookmarks.qrc
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    BOOKMARKS_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteeditorapi
    symboltreeview
    liteapi
)