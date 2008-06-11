include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include ${picviz_SOURCE_DIR}/src/libpicviz/parser ${picviz_SOURCE_DIR}/src/libpicviz/props)

#set(CMAKE_SHARED_LINKER_FLAGS "-lm")
set(CMAKE_SHARED_LINKER_FLAGS "-lm -lfl -ly")

BISON_TARGET(picviz ${picviz_SOURCE_DIR}/src/libpicviz/parser/parser.y ${picviz_SOURCE_DIR}/src/libpicviz/parser/parser.c)
FLEX_TARGET(picviz ${picviz_SOURCE_DIR}/src/libpicviz/parser/lexer.l ${picviz_SOURCE_DIR}/src/libpicviz/parser/lexer.c)

add_library(picviz SHARED axis.c image.c line.c plugins.c engine.c render.c values-mapping.c variable.c utils.c parser/parser.c parser/lexer.c props/color.c)

install(TARGETS picviz LIBRARY DESTINATION lib)
