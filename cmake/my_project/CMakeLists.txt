cmake_minimum_required(VERSION 3.14)

project( MyProject)

# get google test

include(FetchContent)
FetchContent_Declare(googleTest 
GIT_REPOSITORY https://github.com/google/googletest
GIT_TAG release-1.11.0 )

FetchContent_GetProperties( googletest)

#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR

if(NOT googletest_POPULATED)
 FetchContent_Populate(googletest)
 add_subdirectory( ${googletest_SOURCE_DIR} ${googletest_BUILD_DIR} )
endif()

add_library(sumLibrary STATIC src/LibraryCode.cpp)
add_executable(myApp src/main.cpp)
target_link_libraries(myApp sumLibrary)

add_executable(testRunner tests/test_sum.cpp)
target_link_libraries(testRunner  sumLibrary)


# project(MyProject)

# set(CMAKE_CXX_STANDARD 17)

# # Enable testing framework
# enable_testing()

# # Add source code
# add_executable(my_app src/main.cpp)

# # Add tests
# add_subdirectory(tests)
