set(TGT liteide)

set(SOURCES
    main.cpp
)

add_executable(${TGT}
    ${SOURCES}
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
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/liteide/bin" 
)