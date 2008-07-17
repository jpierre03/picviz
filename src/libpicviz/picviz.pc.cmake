prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix="${prefix}"
includedir="${prefix}/include/picviz"
libdir="${exec_prefix}/lib"

Name: Picviz
Description: Parallel Coordinates Plot Library
Version: 0.1
Libs: -L${libdir} -lpicviz
Cflags: -I${includedir}/picviz

