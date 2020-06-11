cmake_minimum_required (VERSION 3.0)
cmake_policy(SET CMP0048 NEW)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")

project (program-map VERSION 0.2)
find_package (CUnit)

add_subdirectory (src)
if (CUNIT_FOUND)
add_subdirectory (tests)
endif (CUNIT_FOUND)
