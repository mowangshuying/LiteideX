option(USE_DLVCLIENT "Enable DLV client support" ON)

set(TGT dlvdebugger)

set(SOURCES
    dlvdebuggerplugin.cpp
    dlvdebugger.cpp
    dlvdebuggeroptionfactory.cpp
    dlvdebuggeroption.cpp
)

set(HEADERS
    dlvdebuggerplugin.h
    dlvdebugger_global.h
    dlvdebugger.h
    dlvdebuggeroptionfactory.h
    dlvdebuggeroption.h
)

set(FORMS
    dlvdebuggeroption.ui
)

if(USE_DLVCLIENT)
    list(APPEND SOURCES
        dlvrpcdebugger.cpp
    )
    list(APPEND HEADERS
        dlvrpcdebugger.h
    )
endif()

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
    GDBDEBUGER_LIBRARY
)

if(USE_DLVCLIENT)
    target_compile_definitions(${TGT} PRIVATE
        USE_DLVCLIENT
    )
endif()

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    litedebugapi
    fileutil
    processex
    qtc_gdbmi
)

if(USE_DLVCLIENT)
    target_link_libraries(${TGT} PRIVATE
        Qt5::Network
        dlvclient
        qjsonrpc
    )
endif()