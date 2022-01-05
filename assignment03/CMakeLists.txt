cmake_minimum_required(VERSION 3.17)
project(assignment03)

link_libraries(cs4722  glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
link_directories(lib)

add_executable(part1 part1.cpp)
add_executable(part2 part2.cpp)
add_executable(part3 part3.cpp)

configure_file(fragment_shader.glsl .)
configure_file(vertex_shader.glsl .)
