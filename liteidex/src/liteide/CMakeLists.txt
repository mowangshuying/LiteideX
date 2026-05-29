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

install(SCRIPT "${CMAKE_SOURCE_DIR}/windows_deploy.cmake")
