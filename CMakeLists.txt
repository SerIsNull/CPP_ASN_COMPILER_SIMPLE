# set minimum version of CMake
cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

# set policy
cmake_policy(VERSION 3.16.3)

# set project name
project(asn_encoder
    VERSION 0.0.4
    DESCRIPTION "This is an asn-compiler simple!"
    LANGUAGES CXX
)

# c++17 is necessary for builing (for all targets in this project)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set all the necessary flags for compiler
set(CMAKE_CXX_COMPILE_FLAG ${CMAKE_CXX_COMPILE_FLAGS} -Wall -Wextra)

# add gtest dir for building the test library
add_subdirectory(thirdparty)

# the test turn ON
enable_testing()

# add test directory
add_subdirectory(test)
