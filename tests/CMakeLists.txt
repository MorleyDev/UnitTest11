include_directories (../include)
link_directories (${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

FILE(GLOB_RECURSE UNITTEST11_TESTS_SRC *.cpp)

add_executable(unittest11_tests ${UNITTEST11_TESTS_SRC})
target_link_libraries(unittest11_tests unittest11)
