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
    LITEDEBUG_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    litedebugapi
    litebuildapi
    fileutil
    textoutput
    colorstyle
    symboltreeview
)