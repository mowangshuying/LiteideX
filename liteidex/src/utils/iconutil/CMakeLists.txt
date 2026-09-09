set(TGT iconutil)

add_library(${TGT} STATIC
    iconutil.h
    iconutil.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${QT5_COMPAT_LIB}
)