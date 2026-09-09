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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    mimetype
    navigate
    liteapi
)

if(ENABLE_SVG)
    target_link_libraries(${TGT} PRIVATE
        Qt${QT_VERSION_MAJOR}::Svg
        ${QT5_COMPAT_LIB}
    )
    if(QT_VERSION_MAJOR EQUAL 6)
        # QGraphicsSvgItem moved from Qt6::Svg to Qt6::SvgWidgets
        target_link_libraries(${TGT} PRIVATE Qt6::SvgWidgets)
    endif()
else()
    target_compile_definitions(${TGT} PRIVATE
        QT_NO_SVG
    )
endif()