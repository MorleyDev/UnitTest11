include_directories(${UNITTEST11_SOURCE_DIR}/include)

include(files.cmake)

add_executable(unittest11_tests ${UNITTEST11_TESTS_SRC_FILES})
target_link_libraries(unittest11_tests unittest11)

add_test(units unittest11_tests category=unit)
add_test(examples unittest11_tests category=example)
