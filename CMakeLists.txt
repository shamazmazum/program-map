cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0048 NEW)

project (vn3d VERSION 0.1)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/program-map.ld.in ${CMAKE_CURRENT_BINARY_DIR}/program-map.ld)
add_library (program-map SHARED program-map.c)
set_target_properties (program-map PROPERTIES VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  LINK_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/program-map.ld
  LINK_FLAGS "-Wl,--version-script ${CMAKE_CURRENT_BINARY_DIR}/program-map.ld ${ADDITIONAL_LINK_FLAGS}")

install (TARGETS program-map LIBRARY DESTINATION lib)
install (FILES program-map.h DESTINATION include)
