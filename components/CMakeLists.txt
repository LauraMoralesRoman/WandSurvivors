file(GLOB BEHAVIOR_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(BEHAVIOR_DIR ${BEHAVIOR_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${BEHAVIOR_DIR} AND NOT ${BEHAVIOR_DIR} STREQUAL "CMakeFiles")
        # Define a new library target for each behavior
        file(GLOB BEHAVIOR_SOURCES "${BEHAVIOR_DIR}/*.cpp")

        # Optionally include header files for visibility in IDEs
        file(GLOB BEHAVIOR_HEADERS "${BEHAVIOR_DIR}/*.hpp" "${BEHAVIOR_DIR}/*.h")

		message(STATUS "Found ${BEHAVIOR_DIR} with ${BEHAVIOR_SOURCES} ${BEHAVIOR_HEADERS}")
		add_library(${BEHAVIOR_DIR} SHARED ${BEHAVIOR_SOURCES} ${BEHAVIOR_HEADERS})

        set_target_properties(${BEHAVIOR_DIR} PROPERTIES
            OUTPUT_NAME ${BEHAVIOR_DIR}
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/behaviors_bin"
        )
    endif()
endforeach()
