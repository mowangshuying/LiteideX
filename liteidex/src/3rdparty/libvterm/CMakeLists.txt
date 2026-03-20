#cmake_minimum_required(VERSION 3.10)

# Set target name
set(TGT libvterm)

# Create static library
add_library(${TGT} STATIC
    # Header files (for IDE recognition)
    include/vterm.h
    include/vterm_keycodes.h
    src/rect.h
    src/utf8.h
    src/vterm_internal.h
    
    # Source files
    src/encoding.c
    src/keyboard.c
    src/mouse.c
    src/parser.c
    src/pen.c
    src/screen.c
    src/state.c
    src/unicode.c
    src/vterm.c
)

# Include common configuration
#include(../../liteideutils.cmake)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set C standard (pure C library)
set_target_properties(${TGT} PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
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
    include/vterm.h
    include/vterm_keycodes.h
    DESTINATION include/libvterm
)

# Distribute data files (equivalent to DISTFILES)
install(FILES
    src/encoding/DECdrawing.inc
    src/encoding/DECdrawing.tbl
    src/encoding/uk.inc
    src/encoding/uk.tbl
    src/fullwidth.inc
    DESTINATION share/libvterm
)