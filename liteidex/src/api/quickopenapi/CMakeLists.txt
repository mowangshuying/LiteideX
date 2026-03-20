set(TGT quickopenapi)
# 创建静态库
add_library(${TGT} STATIC
    quickopenapi.h
)

# 定义编译宏
#target_compile_definitions(${TGT} PRIVATE
#    DOCBROWSERAPI_LIBRARY
#)

# 设置头文件路径
target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_link_libraries(${TGT} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::PrintSupport
)
