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
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets

    liteapi
)