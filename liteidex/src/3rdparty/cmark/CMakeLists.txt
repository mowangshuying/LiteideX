set(TGT cmark)

set(HEADERS
    cmark_export.h
    cmark_version.h
    config.h
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
    libcmark.h
)

set(SOURCES
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
    libcmark.cpp
)

add_library(${TGT} STATIC
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${TGT} PUBLIC
    ./
    ./src
    ../
)

set_target_properties(${TGT} PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)

target_link_libraries(${TGT} PUBLIC
    Qt5::Core
)

