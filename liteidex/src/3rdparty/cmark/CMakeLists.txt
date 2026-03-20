#cmake_minimum_required(VERSION 3.10)

# 设置目标名称
set(TGT cmark)

# 创建静态库
add_library(${TGT} STATIC
    # C++ 源文件
    libcmark.cpp
    
    # C 源文件
    src/blocks.c
    src/buffer.c
    src/cmark.c
    src/cmark_ctype.c
    src/commonmark.c
    src/houdini_href_e.c
    src/houdini_html_e.c
    src/houdini_html_u.c
    src/html.c
    src/inlines.c
    src/iterator.c
    src/latex.c
    src/man.c
    src/node.c
    src/references.c
    src/render.c
    src/scanners.c
    src/utf8.c
    src/xml.c
    
    # 头文件（可选，便于 IDE 识别）
    libcmark.h
    src/buffer.h
    src/chunk.h
    src/cmark.h
    src/cmark_ctype.h
    src/houdini.h
    src/inlines.h
    src/iterator.h
    src/node.h
    src/parser.h
    src/references.h
    src/render.h
    src/scanners.h
    src/utf8.h
)

# 引入公共配置
#include(../../liteideutils.cmake)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)


# 定义编译宏
target_compile_definitions(${TGT} PRIVATE
    QT_DEPRECATED_WARNINGS
)

# 设置头文件包含路径
target_include_directories(${TGT} PUBLIC
    ./
    ./src
)

# 设置 C 标准（因包含 .c 文件）
set_target_properties(${TARGET_NAME} PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)