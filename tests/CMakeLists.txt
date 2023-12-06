find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

function(add_gtest TEST_NAME TEST_FILE)
	add_executable(${TEST_NAME} ${TEST_FILE})
	target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES})
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_gtest("Dummy" test_dummy.cpp)
add_gtest("input_handler" test_inputHandler.cpp)
