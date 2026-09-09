set(TGT qt_browser)

# static library
add_library(${TGT} STATIC
	chasewidget.cpp
    chasewidget.h
)

target_link_libraries(${TGT}
   Qt${QT_VERSION_MAJOR}::Core
   Qt${QT_VERSION_MAJOR}::Widgets
   Qt${QT_VERSION_MAJOR}::Gui
   ${QT5_COMPAT_LIB}
)