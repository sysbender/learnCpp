
# cmake version 
# cmake_minimum_required( MIN   3.5 )
cmake_minimum_required(VERSION 4.1.0...4.2.0)

# project
project(hello 
    VERSION 0.0.1 
    LANGUAGES CXX 
    )


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# what to build
add_executable(hello hello.cpp)

# flag
#target_compile_features(HelloAppBinary PRIVATE cxx_std_20)
