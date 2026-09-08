set(TGT gopls)

set(SOURCES
    goplsplugin.cpp
    goplsclient.cpp
    goplssearchresults.cpp
    goplsoption.cpp
    goplsoptionfactory.cpp
)

set(HEADERS
    goplsplugin.h
    goplsclient.h
    goplssearchresults.h
    gopls_global.h
    goplsoption.h
    goplsoptionfactory.h
)

set(FORMS
    goplsoption.ui
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteapi
    liteenvapi
    golangastapi
    liteeditorapi
    litefindapi
    fileutil
)
