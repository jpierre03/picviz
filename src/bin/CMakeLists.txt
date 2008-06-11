LINK_DIRECTORIES(${picviz_SOURCE_DIR}/src/libpicviz/)
LINK_LIBRARIES(picviz)
include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include)
add_executable(picviz picviz.c)
