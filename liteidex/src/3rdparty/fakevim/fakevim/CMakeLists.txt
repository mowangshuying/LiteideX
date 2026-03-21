set(TGT fakevim)

add_library(${TGT} STATIC 
	fakevimhandler.h 
	fakevimactions.h
	fakevimhandler.cpp 
	fakevimactions.cpp

	utils/hostosinfo.h
	utils/qtcassert.cpp
	utils/qtcassert.h
	utils/utils_global.h
)

target_link_libraries(${TGT}
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets

	processex
)

target_include_directories(${TGT} PUBLIC
    ./
	../
	../../
)

target_compile_definitions(${TGT} PRIVATE
    FAKEVIM_STANDALONE
)