set(TGT elidedlabel)

add_library(${TGT} STATIC 
	elidedlabel.h
    elidedlabel.cpp
)

target_include_directories(${TGT} PUBLIC
	./
	../
)

target_link_libraries( ${TGT} PUBLIC
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Widgets
	${QT5_COMPAT_LIB}
)