cmake_minimum_required(VERSION 3.10)

# 设置目标名称
set(TGT qtc_texteditor)

# 创建静态库
add_library(${TGT} STATIC
    # 头文件（便于 IDE 识别）
    texteditor_global.h
    tabsettings.h
    syntaxhighlighter.h
    itexteditor.h
    basetextdocumentlayout.h
    generichighlighter/specificrules.h
    generichighlighter/rule.h
    generichighlighter/reuse.h
    generichighlighter/progressdata.h
    generichighlighter/keywordlist.h
    generichighlighter/itemdata.h
    generichighlighter/includerulesinstruction.h
    generichighlighter/highlighterexception.h
    generichighlighter/highlighter.h
    generichighlighter/highlightdefinitionmetadata.h
    generichighlighter/highlightdefinitionhandler.h
    generichighlighter/highlightdefinition.h
    generichighlighter/dynamicrule.h
    generichighlighter/context.h
    katehighlighter.h
    generichighlighter/manager2.h
    colorscheme.h
    autocompleter.h
    basetextblockselection.h
    
    # 源文件
    tabsettings.cpp
    syntaxhighlighter.cpp
    itexteditor.cpp
    basetextdocumentlayout.cpp
    generichighlighter/specificrules.cpp
    generichighlighter/rule.cpp
    generichighlighter/progressdata.cpp
    generichighlighter/keywordlist.cpp
    generichighlighter/itemdata.cpp
    generichighlighter/includerulesinstruction.cpp
    generichighlighter/highlighter.cpp
    generichighlighter/highlightdefinitionmetadata.cpp
    generichighlighter/highlightdefinitionhandler.cpp
    generichighlighter/highlightdefinition.cpp
    generichighlighter/dynamicrule.cpp
    generichighlighter/context.cpp
    katehighlighter.cpp
    generichighlighter/manager2.cpp
    colorscheme.cpp
    autocompleter.cpp
    basetextblockselection.cpp
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::PrintSupport

    colorstyle
)

# 定义编译宏
target_compile_definitions(${TGT} PRIVATE
    TEXTEDITOR_LIBRARY
)

# 设置头文件包含路径
target_include_directories(${TGT} PUBLIC
    ./
    ../
    ../../api
)