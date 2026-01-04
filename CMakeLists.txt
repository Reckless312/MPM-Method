cmake_minimum_required(VERSION 4.1)
project(MPM_Method LANGUAGES C CXX CUDA)

set(CMAKE_CUDA_STANDARD 20)

set(SOURCE_FILES glad.c main.cpp
        kernel.cu)

add_executable(MPM_Method ${SOURCE_FILES})

set_target_properties(MPM_Method PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(MPM_Method GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp)