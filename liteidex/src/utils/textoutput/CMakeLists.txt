# Set target name
set(TGT textoutput)

# Create static library
add_library(${TGT} STATIC
    textoutput.h
    terminaledit.h
    textoutput.cpp
    terminaledit.cpp
)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
    ../
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Widgets

    liteapi
    colorstyle
)