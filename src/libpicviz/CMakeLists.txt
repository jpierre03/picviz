add_subdirectory(plugins)
#add_subdirectory(bindings)

include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include ${picviz_SOURCE_DIR}/src/libpicviz/parser ${picviz_SOURCE_DIR}/src/libpicviz/props)

#set(CMAKE_SHARED_LINKER_FLAGS "-lm -lfl -ly")
configure_file(
${picviz_SOURCE_DIR}/src/libpicviz/picviz.pc.cmake
${picviz_BINARY_DIR}/src/libpicviz/picviz.pc
)

BISON_TARGET(picviz ${picviz_SOURCE_DIR}/src/libpicviz/parser/parser.y ${picviz_SOURCE_DIR}/src/libpicviz/parser/parser.c)
FLEX_TARGET(picviz ${picviz_SOURCE_DIR}/src/libpicviz/parser/lexer.l ${picviz_SOURCE_DIR}/src/libpicviz/parser/lexer.c)

add_library(picviz SHARED axis.c debug.c image.c line.c plugins.c engine.c render.c values-mapping.c variable.c utils.c parser/parser.c parser/lexer.c props/color.c)

target_link_libraries(picviz "-lm -ldl")

install(TARGETS picviz LIBRARY DESTINATION lib)
INSTALL(FILES
		include/axis.h
		include/common.h
		include/debug.h
		include/defaults.h
		include/engine.h
		include/image.h
		include/line.h
		include/linuxlist.h
		include/pcimage.h
		include/picviz.h
		include/plugins.h
		include/properties.h
		include/render.h
		include/types.h
		include/values-mapping.h
		include/variable.h
	DESTINATION include/picviz
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

INSTALL(FILES ${picviz_BINARY_DIR}/src/libpicviz/picviz.pc
	DESTINATION lib/pkgconfig/ )

