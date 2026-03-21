# Set target name
set(TGT symboltreeview)

# Create static library
add_library(${TGT} STATIC
    symboltreeview.h
    symboltreeview.cpp
)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
    ../
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)