set(TGT colorstyle)

add_library(${TGT} STATIC
    colorstyle.cpp
    colorstyle.h
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_link_libraries(${TGT}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)