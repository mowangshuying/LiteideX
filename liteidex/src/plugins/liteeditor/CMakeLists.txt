set(TGT liteeditor)

set(SOURCES
    liteeditorplugin.cpp
    liteeditor.cpp
    liteeditorfile.cpp
    liteeditorfilefactory.cpp
    liteeditoroption.cpp
    liteeditoroptionfactory.cpp
    liteeditorwidgetbase.cpp
    liteeditorwidget.cpp
    litecompleter.cpp
    litewordcompleter.cpp
    liteeditormark.cpp
    highlightermanager.cpp
    katehighlighterfactory.cpp
    codecompleter.cpp
    functiontooltip.cpp
    faketooltip.cpp
    snippetapi.cpp
    wordapi.cpp
    editorapimanager.cpp
    katetextlexer.cpp
)

set(HEADERS
    liteeditorplugin.h
    liteeditor_global.h
    liteeditor.h
    liteeditorfile.h
    liteeditorfilefactory.h
    liteeditoroption.h
    liteeditoroptionfactory.h
    liteeditorwidgetbase.h
    liteeditorwidget.h
    litecompleter.h
    litewordcompleter.h
    liteeditormark.h
    highlightermanager.h
    katehighlighterfactory.h
    codecompleter.h
    functiontooltip.h
    faketooltip.h
    snippetapi.h
    wordapi.h
    editorapimanager.h
    katetextlexer.h
)

set(FORMS
    liteeditoroption.ui
)

set(RESOURCES
    liteeditor.qrc
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
    LITEEDITOR_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Xml
    liteeditorapi
    quickopenapi
    extension
    mimetype
    colorstyle
    editorutil
    folderview
    navigate
    qtc_texteditor
    qtc_editutil
    treemodelcompleter
    elidedlabel
    qjson
    libucd
)