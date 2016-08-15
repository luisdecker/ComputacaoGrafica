cmake_minimum_required(VERSION 2.6)
project(trabalho1cg)

add_executable(trabalho1cg main.cpp)

install(TARGETS trabalho1cg RUNTIME DESTINATION bin)

add_subdirectory(src)