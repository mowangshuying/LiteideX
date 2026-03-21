set(TGT quickopen)

set(SOURCES
    quickopenplugin.cpp
    quickopenwidget.cpp
    quickopenmanager.cpp
    quickopenfiles.cpp
    quickopenlines.cpp
    quickopenhelp.cpp
    quickopeneditor.cpp
    quickopenmimetype.cpp
    quickopenoption.cpp
    quickopenoptionfactory.cpp
    quickopenaction.cpp
    quickopenfolder.cpp
    quickopenfilesystem.cpp
)

set(HEADERS
    quickopenplugin.h
    quickopen_global.h
    quickopenwidget.h
    quickopenmanager.h
    quickopenfiles.h
    quickopenlines.h
    quickopenhelp.h
    quickopeneditor.h
    quickopenmimetype.h
    quickopenoption.h
    quickopenoptionfactory.h
    quickopenaction.h
    quickopenfolder.h
    quickopenfilesystem.h
)

set(FORMS
    quickopenoption.ui
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
    QUICKOPEN_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    quickopenapi
    fileutil
    folderview
    qtc_editutil
)