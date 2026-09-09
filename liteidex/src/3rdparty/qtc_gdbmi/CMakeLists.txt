set(TGT qtc_gdbmi)

add_library(${TGT} STATIC 
    gdbmi.cpp
    gdbmi.h
)

target_link_libraries(${TGT} PUBLIC 
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
)

target_include_directories(${TGT} PUBLIC 
    ./
    ../
)
