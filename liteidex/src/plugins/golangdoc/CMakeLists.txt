set(TGT golangdoc)

set(SOURCES
    golangdocplugin.cpp
    golangdoc.cpp
    golangdocoptionfactory.cpp
    golangdocoption.cpp
    finddocwidget.cpp
    findapiwidget.cpp
)

set(HEADERS
    golangdocplugin.h
    golangdoc_global.h
    golangdoc.h
    golangdocoptionfactory.h
    golangdocoption.h
    finddocwidget.h
    findapiwidget.h
)

set(FORMS
    golangdocoption.ui
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
    GOLANGDOC_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Xml
    liteenvapi
    golangdocapi
    liteeditorapi
    documentbrowser
    fileutil
    processex
    htmlutil
    golangapi
    qtc_editutil
    qjson
    qt_browser
    liteapi
)