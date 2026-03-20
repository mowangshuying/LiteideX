set(TGT elidedlabel)

add_library(${TGT} STATIC 
	elidedlabel.h
    elidedlabel.cpp
)

target_link_libraries( ${TGT} PUBLIC
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)