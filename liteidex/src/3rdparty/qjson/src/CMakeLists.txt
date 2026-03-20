#cmake_minimum_required(VERSION 3.10)

# Set target name
set(TGT json)

# Set version
set(VERSION 0.7.1)

# Private headers (internal use)
set(PRIVATE_HEADERS
    json_parser.hh
    json_scanner.h
    location.hh
    parser_p.h
    position.hh
    qjson_debug.h
    stack.hh
)

# Public headers (for external use)
set(PUBLIC_HEADERS
    parser.h
    parserrunnable.h
    qobjecthelper.h
    serializer.h
    serializerrunnable.h
    qjson_export.h
)

# Create static library
add_library(${TGT} STATIC
    # Header files
    ${PRIVATE_HEADERS}
    ${PUBLIC_HEADERS}
    
    # Source files
    json_parser.cc
    json_scanner.cpp
    parser.cpp
    parserrunnable.cpp
    qobjecthelper.cpp
    serializer.cpp
    serializerrunnable.cpp
)

# Include common configuration
#include(../../../liteideutils.cmake)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
)

# Set target properties
set_target_properties(${TGT} PROPERTIES
    VERSION ${VERSION}
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
)

# Install configuration (optional)
install(TARGETS ${TGT}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES
    ${PUBLIC_HEADERS}
    DESTINATION include/qjson
)