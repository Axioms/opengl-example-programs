cmake_minimum_required(VERSION 3.17)
project(assignment04-solved)

link_libraries(cs4722  glfw3 opengl32 glu32)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)
link_directories(lib)

configure_file(fragment_shader.glsl .)
configure_file(vertex_shader.glsl .)




add_executable(0-base 0-base.cpp)
add_executable(1-mix-colors 1-mix-colors.cpp)
add_executable(2-stick-to-ground 2-stick-to-ground.cpp)
add_executable(3-eyes-level 3-eyes-level.cpp)
add_executable(4-panning 4-panning.cpp)
add_executable(5-monolith 5-monolith.cpp)