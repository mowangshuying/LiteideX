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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}

    liteapi
    diff_match_patch
)