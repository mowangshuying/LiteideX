set(TGT golangpackage)

set(SOURCES
    golangpackageplugin.cpp
    filepathmodel.cpp
    golangpackageoption.cpp
    golangpackageoptionfactory.cpp
    packagebrowser.cpp
    gotool.cpp
    packageproject.cpp
    packagetree.cpp
    packageprojectfactory.cpp
)

set(HEADERS
    golangpackageplugin.h
    golangpackage_global.h
    filepathmodel.h
    golangpackageoption.h
    golangpackageoptionfactory.h
    packagebrowser.h
    gotool.h
    packageproject.h
    packagetree.h
    packageprojectfactory.h
)

set(FORMS
    golangpackageoption.ui
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    GOLANGPACKAGE_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteenvapi
    golangdocapi
    fileutil
    processex
    symboltreeview
    qjson
)