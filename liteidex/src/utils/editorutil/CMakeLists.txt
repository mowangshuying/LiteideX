set(TGT editorutil)

add_library(${TGT} STATIC
    editorutil.h
    difflib.h
    libucd.h
    checkdata.h
    editorutil.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Widgets

    liteapi
    diff_match_patch
)