include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include)
link_directories(${picviz_SOURCE_DIR}/src/libpicviz/)
add_executable(pcv pcv.c)
target_link_libraries(pcv picviz)

INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/pcv   DESTINATION bin)
