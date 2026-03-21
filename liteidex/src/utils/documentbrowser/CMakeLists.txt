# Set target name
set(TGT documentbrowser)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


# Create static library
add_library(${TGT} STATIC
    documentbrowser.h
    documentbrowserfactory.h
    documentbrowser.cpp
    documentbrowserfactory.cpp
)

# Set header include paths
target_include_directories(${TGT} PUBLIC
    ./
)

# Link dependencies (no find_package)
target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Widgets
    liteapi
    extension
    cmark
    docbrowserapi
)