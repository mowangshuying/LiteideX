if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
find_program(QT_DEPLOY_QT NAMES windeployqt)
add_custom_command(TARGET liteide POST_BUILD
    COMMAND "${QT_DEPLOY_QT}" 
            --dir "${CMAKE_SOURCE_DIR}/liteide/bin"     
            --release                                    
            --no-translations                            
            --no-compiler-runtime                        
            "$<TARGET_FILE:liteapp>"                     
            "$<TARGET_FILE:bookmarks>"
            "$<TARGET_FILE:dlvdebugger>"
            "$<TARGET_FILE:fakevimedit>"
            "$<TARGET_FILE:filebrowser>"
            "$<TARGET_FILE:golangast>"
            "$<TARGET_FILE:golangpls>"
            "$<TARGET_FILE:golangdoc>"
            "$<TARGET_FILE:golangedit>"
            "$<TARGET_FILE:golangfmt>"
            "$<TARGET_FILE:golangplay>"
            "$<TARGET_FILE:golangpresent>"
            "$<TARGET_FILE:helloliteide>"
            "$<TARGET_FILE:imageeditor>"
            "$<TARGET_FILE:jsonedit>"
            "$<TARGET_FILE:litebuild>"
            "$<TARGET_FILE:litedebug>"
            "$<TARGET_FILE:liteeditor>"
            "$<TARGET_FILE:liteenv>"
            "$<TARGET_FILE:litefind>"
            "$<TARGET_FILE:litetty>"
            "$<TARGET_FILE:markdown>"
            "$<TARGET_FILE:qsqleditor>"
            "$<TARGET_FILE:quickopen>"
            "$<TARGET_FILE:rustedit>"
            "$<TARGET_FILE:terminal>"
            "$<TARGET_FILE:welcome>"
    COMMENT "Running windeployqt to deploy Qt dependencies to bin directory..."
)
endif()