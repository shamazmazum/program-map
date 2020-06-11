include_directories (${CUNIT_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)

add_executable (run-tests EXCLUDE_FROM_ALL tests.c)
target_link_libraries (run-tests program-map ${CUNIT_LIBRARY})

add_custom_target (check
  echo "Test..." > success && ./run-tests
  COMMENT "Run tests"
  DEPENDS run-tests)
