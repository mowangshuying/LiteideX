set(TGT markdown)

set(SOURCES
    markdownplugin.cpp
    htmlpreview.cpp
    markdownedit.cpp
    markdownbatchbrowser.cpp
)

set(HEADERS
    markdownplugin.h
    markdown_global.h
    htmlpreview.h
    markdownedit.h
    markdownbatchbrowser.h
)

set(FORMS
    markdownbatchwidget.ui
)

set(RESOURCES
    markdown.qrc
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
    MARKDOWN_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    cmark
    liteapi
)