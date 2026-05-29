set(TGT liteide)

set(SOURCES
    main.cpp
)

add_executable(${TGT}
    ${SOURCES}
    liteide.rc
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Xml
    liteapp
)

if(WIN32)
    target_link_libraries(${TGT} PRIVATE
        ole32.lib
        shell32.lib
    )
endif()

set_target_properties(${TGT} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/liteide/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/liteide/bin"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/liteide/lib/liteide"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/liteide/lib/liteide"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
    find_program(QT_DEPLOY_QT NAMES windeployqt)

    if(QT_DEPLOY_QT)
        install(CODE "
            message(STATUS \">>>windeployqt deployed automatically...\")
            if(CMAKE_INSTALL_CONFIG_NAME STREQUAL \"Release\")
                set(DEPLOY_ARGS --release)
            endif()
            execute_process(
                COMMAND \"${QT_DEPLOY_QT}\" 
                        --dir \"${CMAKE_SOURCE_DIR}/liteide/bin\"     
                        \${DEPLOY_ARGS}
                        --no-translations                            
                        --no-compiler-runtime                        
                        \"${CMAKE_SOURCE_DIR}/liteide/bin/liteapp.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/bookmarks.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/dlvdebugger.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/fakevimedit.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/filebrowser.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/golangast.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/golangpls.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/golangdoc.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/golangedit.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/golangfmt.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/golangplay.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/golangpresent.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/helloliteide.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/imageeditor.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/jsonedit.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/litebuild.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/litedebug.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/liteeditor.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/liteenv.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/litefind.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/litetty.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/markdown.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/qsqleditor.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/quickopen.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/rustedit.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/terminal.dll\"
                        \"${CMAKE_SOURCE_DIR}/liteide/lib/liteide/plugins/welcome.dll\"
                WORKING_DIRECTORY \"${CMAKE_SOURCE_DIR}/liteide/bin\"
                RESULT_VARIABLE DEPLOY_RESULT
            )
            if(NOT DEPLOY_RESULT EQUAL 0)
                message(FATAL_ERROR \"windeployqt 执行失败！\")
            endif()
        ")
    else()
        message(WARNING "windeployqt not found! Qt dependencies will not be deployed automatically.")
    endif()
endif()