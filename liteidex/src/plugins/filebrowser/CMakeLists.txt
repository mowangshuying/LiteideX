set(TGT filebrowser)

set(SOURCES
    filebrowserplugin.cpp
    filebrowser.cpp
    filebrowseroptionfactory.cpp
    filebrowseroption.cpp
)

set(HEADERS
    filebrowserplugin.h
    filebrowser_global.h
    filebrowser.h
    filebrowseroptionfactory.h
    filebrowseroption.h
)

set(FORMS
    filebrowseroption.ui
)

set(RESOURCES
    filebrowser.qrc
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
    FILEBROWSER_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    fileutil
    folderview
    symboltreeview
    litebuildapi
    golangdocapi
)