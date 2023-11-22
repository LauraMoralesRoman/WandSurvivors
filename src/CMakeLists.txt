add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(WandSurvivors ${CMAKE_SOURCE_DIR}/lib/libraylib.so)

add_custom_target(run
	COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
	COMMENT "Running the game...")
