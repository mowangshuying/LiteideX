set(TGT treemodelcompleter)

add_library(${TGT} STATIC
  treemodelcompleter.cpp
  treemodelcompleter.h
)

target_link_libraries(${TGT}
	Qt5::Core
    Qt5::Gui
	Qt5::Widgets
)