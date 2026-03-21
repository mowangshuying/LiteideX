set(TGT golangedit)

set(SOURCES
    golangeditplugin.cpp
    golangedit.cpp
    golangfilesearch.cpp
    golanghighlighter.cpp
    golanghighlighterfactory.cpp
    golangtextlexer.cpp
    golangeditoption.cpp
    golangeditoptionfactory.cpp
    goaddtagsdialog.cpp
    goplsfilesearch.cpp
    goremovetagsdialog.cpp
)

set(HEADERS
    golangeditplugin.h
    golangedit_global.h
    golangedit.h
    golangfilesearch.h
    golanghighlighter.h
    golanghighlighterfactory.h
    golangtextlexer.h
    golangeditoption.h
    golangeditoptionfactory.h
    goaddtagsdialog.h
    goplsfilesearch.h
    goremovetagsdialog.h
)

set(FORMS
    golangeditoption.ui
    goaddtagsdialog.ui
    goremovetagsdialog.ui
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
    GOLANGEDIT_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteenvapi
    litefindapi
    liteeditorapi
    litebuildapi
    quickopenapi
    processex
    fileutil
    textoutput
    colorstyle
    qtc_texteditor
    cplusplus
    qtc_editutil
)