set(TGT folderview)

add_library(${TGT} STATIC
    folderview.h
    basefoldeview.h
    folderlistview.h
    folderlistmodel.h
    filesystemmodelex.h
    folderdialog.h
    abstractmultiproxymodel_p.h
    abstractmultiproxymodel.h
    dirsortfilterproxymodel.h
    multifoldermodel.h
    multiindexmodel_p.h
    multiindexmodel.h
    multifolderview.h
    folderview.cpp
    basefolderview.cpp
    folderlistview.cpp
    folderlistmodel.cpp
    filesystemmodelex.cpp
    folderdialog.cpp
    abstractmultiproxymodel.cpp
    dirsortfilterproxymodel.cpp
    multifoldermodel.cpp
    multiindexmodel.cpp
    multifolderview.cpp
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Widgets

    liteapi
    symboltreeview
)