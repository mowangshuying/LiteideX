set(TGT welcome)

add_library(${TGT} SHARED 
    #../../pch/liteide_gui_pch.h
	# headers
    welcomeplugin.h
    welcome_global.h
    welcomebrowser.h
    litedoc.h

    #src
    welcomeplugin.cpp
    welcomebrowser.cpp
    litedoc.cpp
)

target_compile_definitions(${TGT} PRIVATE
    LITEAPP_LIBRARY
    WELCOME_LIBRARY
)

target_link_libraries(${TGT}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Xml

    cmark
    liteapi
    docbrowserapi
    documentbrowser
    elidedlabel
    htmlutil
    extension
)