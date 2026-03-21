set(TGT golangapi)

add_library(${TGT} STATIC 
	golangapi.h
    golangapi.cpp
)

target_link_libraries(${TGT}
    Qt5::Core
    liteapi
)