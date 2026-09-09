# Set target name
set(TGT modelproject)

# Create static library
add_library(${TGT} STATIC
    modelprojectimpl.h
    modelfileimpl.h
    modelprojectimpl.cpp
    modelfileimpl.cpp
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
    fileutil
)
