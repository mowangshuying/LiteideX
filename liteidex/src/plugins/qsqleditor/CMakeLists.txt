set(TGT qsqleditor)

set(SOURCES
	qsqldbfile.cpp
	qsqleditor.cpp
	qsqleditorplugin.cpp
	qsqlfilefactory.cpp
	sqlitemdelegate.cpp
	sqlitefile.cpp
	sqltablemodel.cpp
	tableviewwidget.cpp
)

set(HEADERS 
	qsqldbfile.h
	qsqleditor.h
	qsqleditorplugin.h
	qsqleditor_global.h
	qsqlfilefactory.h
	sqlitefile.h
	sqlitemdelegate.h
	sqltablemodel.h
	tableviewwidget.h
)

set(FORMS 
	qsqleditor.ui
	tableviewwidget.ui
)

add_library(${TGT} SHARED
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_include_directories(${TGT} PUBLIC
    ./
)

target_compile_definitions(${TGT} PRIVATE
	QSQLEDITOR_LIBRARY
)

target_link_libraries(${TGT} PRIVATE
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	Qt5::Sql
	liteapi
)