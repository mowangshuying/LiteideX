# Set target name
set(TGT mimetype)

# Create static library
add_library(${TGT} STATIC
    # Header files
    mimetype.h
    
    # Source files
    mimetype.cpp
)

# Include common configuration
#include(../../liteideutils.cmake)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    liteapi
)

# Install configuration (optional)
#install(TARGETS ${TGT}
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)

#install(FILES
#    mimetype.h
#    DESTINATION include/mimetype
#)