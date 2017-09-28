project(ok_galg)
cmake_minimum_required(VERSION 2.6)

add_compile_options(-std=c++11)

include_directories(include)

add_library(${PROJECT_NAME} SHARED include/ok_galg/indiv.h include/ok_galg/galg.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

install (FILES include/ok_galg/galg.h DESTINATION include/${PROJECT_NAME})
