# Set target name
set(TGT processex)

# Create static library
add_library(${TGT} STATIC
    processex.h
    processex.cpp
)

# 
target_compile_definitions(${TGT} PRIVATE
    UNICODE
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