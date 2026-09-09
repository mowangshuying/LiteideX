set(TGT golangast)

set(SOURCES
    golangastplugin.cpp
    golangast.cpp
    golangasticon.cpp
    astwidget.cpp
    golangsymbol.cpp
    golangastoption.cpp
    golangastoptionfactory.cpp
)

set(HEADERS
    golangastplugin.h
    golangast_global.h
    golangast.h
    golangasticon.h
    astwidget.h
    golangastitem.h
    golangsymbol.h
    golangastoption.h
    golangastoptionfactory.h
)

set(FORMS
    golangastoption.ui
)

set(RESOURCES
    golangast.qrc
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
    GOLANGAST_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    liteapi
    golangastapi
    quickopenapi
    liteenvapi
    symboltreeview
    qtc_editutil
)