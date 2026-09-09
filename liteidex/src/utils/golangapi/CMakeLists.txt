set(TGT golangapi)

add_library(${TGT} STATIC 
	golangapi.h
    golangapi.cpp
)

target_link_libraries(${TGT}
    Qt${QT_VERSION_MAJOR}::Core
    ${QT5_COMPAT_LIB}
    liteapi
)