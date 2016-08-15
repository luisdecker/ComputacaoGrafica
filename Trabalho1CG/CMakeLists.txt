cmake_minimum_required(VERSION 2.6)
project(trabalho1cg)

set (CMAKE_CXX_STANDARD 11)
aux_source_directory(. src_list)
add_executable(trabalho1cg ${src_list})

install(TARGETS trabalho1cg RUNTIME DESTINATION bin)

add_subdirectory(src)