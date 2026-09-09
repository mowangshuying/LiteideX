set(TGT diff_match_patch)

add_library(${TGT} STATIC
	diff_match_patch.h
    diff_match_patch.cpp
)

target_include_directories(${TGT} PUBLIC
   ./
   ../
)

target_link_libraries(${TGT}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}

    liteapi
)