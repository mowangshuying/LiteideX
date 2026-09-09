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
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Widgets
	${QT5_COMPAT_LIB}

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