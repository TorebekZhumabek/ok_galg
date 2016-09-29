project(tsp_galg)
cmake_minimum_required(VERSION 2.6)

add_compile_options(-std=c++11)
add_compile_options(-pthread)

find_package(PkgConfig REQUIRED)
pkg_check_modules(YamlCpp yaml-cpp)
find_package (Threads)

include_directories(include ${YamlCpp_INCLUDE_DIRS})
LINK_DIRECTORIES(/usr/local/lib)

add_executable(tsp main/tsp.cpp include/travel.h src/travel.cpp)
target_link_libraries(tsp yaml-cpp ${CMAKE_THREAD_LIBS_INIT})
