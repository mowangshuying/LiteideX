set(TGT tabwidget)

add_library(${TGT} STATIC
    litetabwidget.h
    litetabwidget.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Widgets

    liteapi
)