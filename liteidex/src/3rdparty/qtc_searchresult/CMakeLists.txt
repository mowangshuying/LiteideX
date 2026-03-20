cmake_minimum_required(VERSION 3.10)

# 设置目标名称
set(TGT qtc_searchresult)

# 创建静态库
add_library(${TGT} STATIC
    # 头文件
    searchresultcolor.h
    searchresulttreeitemdelegate.h
    searchresulttreeitemroles.h
    searchresulttreeitems.h
    searchresulttreemodel.h
    searchresulttreeview.h
    searchresultitem.h
    searchresultwidget.h
    
    # 源文件
    searchresulttreeitemdelegate.cpp
    searchresulttreeitems.cpp
    searchresulttreemodel.cpp
    searchresulttreeview.cpp
    searchresultwidget.cpp
)

# 引入公共配置
#include(../../liteideutils.cmake)

target_link_libraries(${TGT} PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# 设置头文件包含路径
target_include_directories(${TGT} PUBLIC
   ./
   ../
)

# Qt 依赖（按需启用）
# find_package(Qt5 COMPONENTS Widgets REQUIRED)
# target_link_libraries(${TGT} PRIVATE Qt5::Widgets)