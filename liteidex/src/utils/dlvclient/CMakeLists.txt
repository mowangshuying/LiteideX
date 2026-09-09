set(TGT dlvclient)

set(SOURCES
    dlvclient.cpp
    varianthelper.cpp
)

set(HEADERS
    dlvclient.h
    dlvtypes.h
    varianthelper.h
)

add_library(${TGT} STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    ${QT5_COMPAT_LIB}
    qjsonrpc
)