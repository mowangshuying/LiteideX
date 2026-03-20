cmake_minimum_required(VERSION 3.10)

# Set target name
set(TGT qtc_editutil)

# Create static library
add_library(${TGT} STATIC
    # Header files
    filterlineedit.h
    fancylineedit.h
    uncommentselection.h
    utils_global.h
    
    # Source files
    filterlineedit.cpp
    fancylineedit.cpp
    uncommentselection.cpp
)

# Include common configuration
#include(../../liteideutils.cmake)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
)

# Disable warning flags (equivalent to QMAKE_CFLAGS_WARN_ON -=)
target_compile_options(${TGT} PRIVATE
    -w
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Widgets
    Qt5::Core
)

# Install configuration (optional)
#install(TARGETS ${TGT}
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)

#install(FILES
#    filterlineedit.h
#    fancylineedit.h
#    uncommentselection.h
#    utils_global.h
#    DESTINATION include/qtc_editutil
#)