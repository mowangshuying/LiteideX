# 设置目标名称
set(TGT qtc_itemview)

# 创建静态库
add_library(${TGT} STATIC
    # 头文件
    opendocumentstreeview.h
    itemviews.h
    proxymodel.h
    
    # 源文件
    opendocumentstreeview.cpp
    itemviews.cpp
    proxymodel.cpp
    
    # 资源文件
    qtc_itemview.qrc
)

# 引入公共配置
#include(../../liteideutils.cmake)

# 设置头文件包含路径
target_include_directories(${TGT} PUBLIC
    ./
    ../
)

# 链接依赖（无需 find_package）
target_link_libraries(${TGT} PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
)

# 安装配置（可选）
#install(TARGETS ${TGT}
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)

#install(FILES
#    opendocumentstreeview.h
#    itemviews.h
#    proxymodel.h
#    DESTINATION include/qtc_itemview
#)