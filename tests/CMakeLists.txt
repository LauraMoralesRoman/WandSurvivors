find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(./resources/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/resources)

add_definitions(-DTEST_RESOURCES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources")

function(add_gtest TEST_NAME TEST_FILE)
	add_executable(${TEST_NAME} ${TEST_FILE})
	target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES} core_lib)
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_gtest("ModuleLoad" components/test_module_load.cpp)
add_gtest("ModuleReload" components/test_module_reload.cpp)
add_gtest("EntityManager" components/test_entity_manager.cpp)
add_gtest("input_system" input/test_inputSystem.cpp)
