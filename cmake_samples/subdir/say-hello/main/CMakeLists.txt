cmake_minimum_required( VERSION 3.12)

add_executable( cmake-good main.cpp )

target_link_libraries( cmake-good PRIVATE say-hello )