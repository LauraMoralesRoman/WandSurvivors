find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(./resources/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/resources)

add_definitions(-DTEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources")

function(add_gtest TEST_NAME TEST_FILE)
	add_executable(${TEST_NAME} ${TEST_FILE})
	target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES} core_lib testing_utils)
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

file(GLOB_RECURSE TEST_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/**/test_*.cpp
)

message("Found the following test sources:")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE) # Get the file name without extension
	string(REGEX REPLACE "^test_" "" TEST_TRIMMED "${TEST_NAME}")

	message("	${TEST_FILE} -> ${TEST_TRIMMED}")

	add_gtest(${TEST_NAME} ${TEST_FILE})
endforeach()
