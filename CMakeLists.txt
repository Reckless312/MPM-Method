cmake_minimum_required(VERSION 4.1)
project(MPM_Method LANGUAGES C CXX CUDA)

set(CMAKE_CUDA_STANDARD 20)

set(SOURCE_FILES src/glad/glad.c src/main.cpp
        src/kernels/kernel.cu
        src/Settings.h
        src/Shaders/Shader.cpp
        src/Shaders/Shader.h
        src/Program/Program.cpp
        src/Program/Program.h
        src/Exceptions/ProgramException.cpp
        src/Exceptions/ProgramException.h
        src/Exceptions/ShaderException.cpp
        src/Exceptions/ShaderException.h
)

add_executable(MPM_Method ${SOURCE_FILES})

set_target_properties(MPM_Method PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(MPM_Method GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp)