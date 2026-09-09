set(TGT htmlutil)

add_library(${TGT} STATIC
    htmlutil.h
    htmlutil.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Xml
    ${QT5_COMPAT_LIB}
)