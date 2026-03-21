set(TGT litedebug)

set(SOURCES
    litedebugplugin.cpp
    debugmanager.cpp
    debugwidget.cpp
    litedebug.cpp
    litedebugoptionfactory.cpp
    litedebugoption.cpp
    selectexternaldialog.cpp
)

set(HEADERS
    litedebugplugin.h
    litedebug_global.h
    debugmanager.h
    debugwidget.h
    litedebug.h
    litedebugoptionfactory.h
    litedebugoption.h
    selectexternaldialog.h
)

set(FORMS
    litedebugoption.ui
    selectexternaldialog.ui
)

set(RESOURCES
    litedebug.qrc
)

add_library(${TGT} MODULE
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    LITEDEBUG_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    litedebugapi
    litebuildapi
    fileutil
    textoutput
    colorstyle
    symboltreeview
)