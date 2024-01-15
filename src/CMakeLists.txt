cmake_minimum_required(VERSION 3.10)

# Define project name
project(MyProject)

# Define a list of libraries
set(PROJECT_LIBRARIES
    libraylib.so
    libspdlog.a
)

# Prepend the library directory path to each library in the list
list(TRANSFORM PROJECT_LIBRARIES PREPEND "${CMAKE_SOURCE_DIR}/lib/")

# Recursively find all .cpp and .hpp files in the source directory
file(GLOB_RECURSE PROJECT_SOURCES "./*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "./*.hpp")

# Create a list of core source files excluding main.cpp
set(CORE_SOURCES ${PROJECT_SOURCES})
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Create a core library
add_library(core_lib ${CORE_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(core_lib ${PROJECT_LIBRARIES})
# Optionally set properties for the core library
# set_target_properties(core_lib PROPERTIES ...)

# Add the executable with the collected source and header files
add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

message("Found the following sources:")
foreach(SOURCE ${PROJECT_SOURCES})
    message("    - ${SOURCE}")
endforeach()

# Link the libraries from the list
target_link_libraries(${CMAKE_PROJECT_NAME} ${PROJECT_LIBRARIES})

# Custom target for running
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMENT "Running the game...")
