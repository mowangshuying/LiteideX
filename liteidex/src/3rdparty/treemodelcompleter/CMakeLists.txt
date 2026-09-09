set(TGT treemodelcompleter)

add_library(${TGT} STATIC
  treemodelcompleter.cpp
  treemodelcompleter.h
)

target_link_libraries(${TGT}
	Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Widgets
	${QT5_COMPAT_LIB}
)