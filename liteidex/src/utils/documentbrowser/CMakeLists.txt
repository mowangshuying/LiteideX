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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    liteapi
    extension
    cmark
    docbrowserapi
)