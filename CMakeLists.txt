cmake_minimum_required (VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

project (program-map VERSION 0.2)

add_library (program-map SHARED program-map.c)
target_compile_options(program-map PRIVATE -Wall -Wextra)
set_target_properties (program-map PROPERTIES VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  C_VISIBILITY_PRESET hidden)

install (TARGETS program-map LIBRARY DESTINATION lib)
install (FILES program-map.h DESTINATION include)
