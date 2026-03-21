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
    Qt5::Core
    Qt5::Widgets
    Qt5::Xml
    Qt5::Network

    liteapi
    libvterm
    ptyqt
)