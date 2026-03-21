set(TGT iconutil)

add_library(${TGT} STATIC
    iconutil.h
    iconutil.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
)