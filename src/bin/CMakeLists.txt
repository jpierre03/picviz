include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include)
link_directories(${picviz_SOURCE_DIR}/src/libpicviz/)
add_executable(pcv picviz.c)
target_link_libraries(pcv picviz)
