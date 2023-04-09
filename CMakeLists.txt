cmake_minimum_required(VERSION 3.14)

project(CS4204_FIB)

find_package(OpenMP REQUIRED)

if(OpenMP_FOUND)
  add_executable (${PROJECT_NAME} "openMP.cpp" Farm/farm.cpp Farm/farm.hpp test.cpp Farm/Task.h Farm/Queue.h)
    target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
else()
    message(FATAL_ERROR "openmp not found!")
endif()


