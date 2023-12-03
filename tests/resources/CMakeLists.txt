###################################
# Component system test resources #
###################################

add_library(basic_module SHARED include/components/basic_module.cpp)
set_target_properties(basic_module PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/components"
)

add_library(no_instance_mod SHARED include/components/no_instance_mod.cpp)
set_target_properties(no_instance_mod PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/components"
)

add_library(basic_reload_v1 SHARED include/components/basic_reload_v1.cpp)
set_target_properties(basic_reload_v1 PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/components"
)

add_library(basic_reload_v2 SHARED include/components/basic_reload_v2.cpp)
set_target_properties(basic_reload_v2 PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/components"
)
