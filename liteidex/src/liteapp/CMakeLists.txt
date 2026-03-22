set(TGT liteapp)

set(SOURCES
    main.cpp
    mainwindow.cpp
    liteapp.cpp
    filemanager.cpp
    editormanager.cpp
    projectmanager.cpp
    pluginmanager.cpp
    actionmanager.cpp
    aboutdialog.cpp
    pluginsdialog.cpp
    mimetypemanager.cpp
    optionmanager.cpp
    newfiledialog.cpp
    optionsbrowser.cpp
    liteappoption.cpp
    liteappoptionfactory.cpp
    toolmainwindow.cpp
    tooldockwidget.cpp
    rotationtoolbutton.cpp
    toolwindowmanager.cpp
    folderproject.cpp
    folderprojectfactory.cpp
    goproxy.cpp
    htmlwidgetmanager.cpp
    textbrowserhtmlwidget.cpp
    splitwindowstyle.cpp
    sidewindowstyle.cpp
    outputoption.cpp
    openeditorswidget.cpp
    idletimer.cpp
    recentmanager.cpp
    multifolderwindow.cpp
    splitfolderwindow.cpp
)

set(HEADERS
    mainwindow.h
    liteapp.h
    liteapp_global.h
    filemanager.h
    editormanager.h
    projectmanager.h
    pluginmanager.h
    actionmanager.h
    aboutdialog.h
    pluginsdialog.h
    mimetypemanager.h
    optionmanager.h
    newfiledialog.h
    optionsbrowser.h
    liteappoption.h
    liteappoptionfactory.h
    toolmainwindow.h
    tooldockwidget.h
    rotationtoolbutton.h
    toolwindowmanager.h
    folderproject.h
    folderprojectfactory.h
    goproxy.h
    cdrv.h
    htmlwidgetmanager.h
    textbrowserhtmlwidget.h
    windowstyle.h
    splitwindowstyle.h
    sidewindowstyle.h
    outputoption.h
    openeditorswidget.h
    idletimer.h
    recentmanager.h
    multifolderwindow.h
    splitfolderwindow.h
)

set(FORMS
    aboutdialog.ui
    pluginsdialog.ui
    newfiledialog.ui
    optionswidget.ui
    liteappoption.ui
    outputoption.ui
)

set(RESOURCES
    liteapp.qrc
)

if(APPLE)
    list(APPEND SOURCES
        macsupport.mm
    )
    list(APPEND HEADERS
        macsupport.h
    )
endif()

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)

target_include_directories(${TGT} PUBLIC
    ./
    ../api
    ../utils
    ../3rdparty
)

target_compile_definitions(${TGT} PRIVATE
    LITEAPP_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Xml
    liteapi
    fileutil
    mimetype
    textoutput
    extension
    folderview
    symboltreeview
    colorstyle
    tabwidget
    elidedlabel
    qtc_editutil
    qtc_itemview
)

if(APPLE)
    target_link_libraries(${TGT} PRIVATE
        AppKit
    )
endif()

set_target_properties(${TGT} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/liteide/bin" 
)