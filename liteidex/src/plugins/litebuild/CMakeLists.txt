set(TGT litebuild)

set(SOURCES
    litebuildplugin.cpp
    litebuild.cpp
    build.cpp
    buildmanager.cpp
    litebuildoptionfactory.cpp
    litebuildoption.cpp
    buildconfigdialog.cpp
)

set(HEADERS
    litebuildplugin.h
    litebuild_global.h
    litebuild.h
    build.h
    buildmanager.h
    litebuildoptionfactory.h
    litebuildoption.h
    buildconfigdialog.h
)

set(FORMS
    litebuildoption.ui
    buildconfigdialog.ui
)

set(RESOURCES
    litebuild.qrc
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
    LITEBUILD_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    liteenvapi
    litebuildapi
    golangdocapi
    elidedlabel
    fileutil
    processex
    textoutput
    colorstyle
)