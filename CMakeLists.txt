#cmake_minimum_required(VERSION 2.6)

project(picviz)

cmake_minimum_required(VERSION 2.4)

configure_file(
${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
${CMAKE_CURRENT_SOURCE_DIR}/config.h
)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${picviz_SOURCE_DIR}/cmake)
FIND_PACKAGE(FLEX)
FIND_PACKAGE(BISON)

add_subdirectory(src)

SET_TARGET_PROPERTIES(picviz PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(picviz PROPERTIES COMPILE_FLAGS "-g")

#summary()

