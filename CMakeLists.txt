cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(10_file_io)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp file_io.h file_io.cpp)

# Use with CMake 3.9.2 and Boost 1.65.1
# Directions
# 1. Enter Boost component names.
# 2. Remove other instances of add_executable()
find_package(Boost 1.65.1 COMPONENTS filesystem REQUIRED)
   if(Boost_FOUND)
     include_directories(${Boost_INCLUDE_DIRS})
     add_executable(${PROJECT_NAME} ${SOURCE_FILES})
     target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
   endif()