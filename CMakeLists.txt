cmake_minimum_required(VERSION 3.0)
project(WandSurvivors)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/interfaces)
include_directories(${CMAKE_SOURCE_DIR}/components)
include_directories(${CMAKE_SOURCE_DIR}/src)

# We'll include the other CMakeLists.txt files
add_subdirectory(components)
add_subdirectory(src)

# Google test configuration
enable_testing()
add_subdirectory(tests)
