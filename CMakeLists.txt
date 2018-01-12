cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(file_io)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp file_io.h file_io.cpp)

find_package(Boost 1.65.1 COMPONENTS filesystem REQUIRED)
   if(Boost_FOUND)
     include_directories(${Boost_INCLUDE_DIRS})
     add_executable(${PROJECT_NAME} ${SOURCE_FILES})
     target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
   endif()