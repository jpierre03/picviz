include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include)
#include_directories(${picviz_SOURCE_DIR}/src/libpicviz/include /usr/include/plplot)
link_directories(${picviz_SOURCE_DIR}/src/libpicviz/)
add_library(picvizoutsvg SHARED outsvg.c)
#add_library(picvizoutpng SHARED outpng.c)
target_link_libraries(picvizoutsvg picviz)
#target_link_libraries(picvizoutpng picviz m plplotd ltdl dl csirocsa csironn qhull freetype)

install(TARGETS picvizoutsvg LIBRARY DESTINATION lib)
#install(TARGETS picvizoutpng LIBRARY DESTINATION lib)

