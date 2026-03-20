#cmake_minimum_required(VERSION 3.10)

# Set target name
set(TGT cplusplus)

# Create static library
add_library(${TGT} STATIC
    # Header files
    cppassert.h
    Lexer.h
    SimpleLexer.h
    Token.h
    BackwardsScanner.h
    
    # Source files
    gokeyword.cpp
    gotypes.cpp
    Keywords.cpp
    Lexer.cpp
    SimpleLexer.cpp
    Token.cpp
    BackwardsScanner.cpp
    gopredecl.cpp
    gobuiltin.cpp
)

# Include common configuration
#include(../../liteideutils.cmake)

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

# Install configuration (optional)
#install(TARGETS ${TGT}
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)

#install(FILES
#    cppassert.h
#    Lexer.h
#    SimpleLexer.h
#    Token.h
#    BackwardsScanner.h
#    DESTINATION include/cplusplus
#)