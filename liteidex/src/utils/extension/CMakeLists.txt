# Set target name
set(TGT extension)

# Create static library
add_library(${TGT} STATIC
    extension.h
    extension.cpp
)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
    ../
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    liteapi
)