# 设置目标名称
set(TGT liteapi)

# 创建静态库
add_library(${TGT} STATIC
    liteobj.h
    liteapi.h
    litehtml.h
    liteqt.h
    liteutil.h
    liteids.h
)

# 引入公共配置
#include(../../liteideapi.cmake)

# 定义编译宏
target_compile_definitions(${TGT} PRIVATE
    LITEAPI_LIBRARY
)

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