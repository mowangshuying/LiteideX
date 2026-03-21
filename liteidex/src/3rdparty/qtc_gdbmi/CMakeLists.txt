set(TGT qtc_gdbmi)

add_library(${TGT} STATIC 
    gdbmi.cpp
    gdbmi.h
)

target_link_libraries(${TGT} PUBLIC 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

target_include_directories(${TGT} PUBLIC 
    ./
    ../
)
