set(TGT vtermwidget)

add_library(${TGT} STATIC
    vtermcolor.h
    vtermwidget.h
    vtermwidgetbase.h
    vtermwidget.cpp
    vtermwidgetbase.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Network
    ${QT5_COMPAT_LIB}

    liteapi
    libvterm
    ptyqt
)