set(TGT fakevimedit)

set(SOURCES
    fakevimeditplugin.cpp
    fakevimedit.cpp
    fakevimeditoption.cpp
    fakevimeditoptionfactory.cpp
)

set(HEADERS
    fakevimeditplugin.h
    fakevimedit_global.h
    fakevimedit.h
    fakevimeditoption.h
    fakevimeditoptionfactory.h
)

set(FORMS
    fakevimeditoption.ui
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_include_directories(${TGT} PUBLIC
    ./
    ../
)

target_compile_definitions(${TGT} PRIVATE
    FAKEVIMEDIT_LIBRARY
    FAKEVIM_STANDALONE
)

target_link_libraries(${TGT} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    litefindapi
    liteeditorapi
    fakevim
)