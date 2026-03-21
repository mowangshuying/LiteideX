set(TGT htmlutil)

add_library(${TGT} STATIC
    htmlutil.h
    htmlutil.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Xml
)