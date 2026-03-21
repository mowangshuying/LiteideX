option(ENABLE_SVG "Enable SVG support" ON)

set(TGT imageeditor)

set(SOURCES
    imageeditor.cpp
    imageeditorfactory.cpp
    imageeditorfile.cpp
    imageeditorplugin.cpp
    imageeditorwidget.cpp
)

set(HEADERS
    imageeditor.h
    imageeditor_global.h
    imageeditorfactory.h
    imageeditorfile.h
    imageeditorplugin.h
    imageeditorwidget.h
)

set(RESOURCES
    imageeditor.qrc
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    IMAGEEDITOR_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    mimetype
    navigate
    liteapi
)

if(ENABLE_SVG)
    target_link_libraries(${TGT} PRIVATE
        Qt5::Svg
    )
else()
    target_compile_definitions(${TGT} PRIVATE
        QT_NO_SVG
    )
endif()