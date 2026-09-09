set(TGT navigate)

add_library(${TGT} STATIC
    navigate.h
    navigate.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    liteapi
)