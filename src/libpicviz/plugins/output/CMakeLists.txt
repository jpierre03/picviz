include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include)
link_directories(${picviz_SOURCE_DIR}/src/libpicviz/)
add_library(picvizoutsvg SHARED outsvg.c)
target_link_libraries(picvizoutsvg picviz)

install(TARGETS picvizoutsvg LIBRARY DESTINATION lib)
