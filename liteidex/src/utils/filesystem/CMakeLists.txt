set(TGT filesystem)

add_library(${TGT} STATIC
    filesystemwidget.h
    filesystemmodel.h
    ../folderview/folderdialog.h
    filesystemwidget.cpp
    filesystemmodel.cpp
    ../folderview/folderdialog.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
    ../folderview
)

target_link_libraries(${TGT} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    ${QT5_COMPAT_LIB}
    liteapi
    symboltreeview
)