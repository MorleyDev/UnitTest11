include_directories(${UNITTEST11_SOURCE_DIR})

include(files.cmake)

add_library(unittest11 ${UNITTEST11_SRC_FILES})
set_target_properties(unittest11 PROPERTIES DEBUG_POSTFIX "-d")

install (TARGETS unittest11 DESTINATION lib)

foreach(HEADER ${UNITTEST11_INCLUDE_FILES})
	string(REPLACE "${UNITTEST11_SOURCE_DIR}" "" DIR ${HEADER})
	string(REGEX MATCH "(.*)[/\\]" DIR2 ${DIR})
	install(FILES ${HEADER} DESTINATION include/${DIR2})
endforeach(HEADER)
