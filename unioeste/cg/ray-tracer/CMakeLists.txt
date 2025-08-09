cmake_minimum_required(VERSION 3.22)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE RAY_FILES "day-three/main.cc" "day-three/*.h")

add_executable(ray ${RAY_FILES})

