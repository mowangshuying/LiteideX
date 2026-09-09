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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
)