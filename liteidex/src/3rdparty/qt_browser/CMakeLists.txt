set(TGT qt_browser)

# static library
add_library(${TGT} STATIC
	chasewidget.cpp
    chasewidget.h
)

target_link_libraries(${TGT}
   Qt5::Core
   Qt5::Widgets
   Qt5::Gui
)