cmake_minimum_required(VERSION 3.16)

project(PhysicsSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(
    PhysicsSim
    src/main.cpp
    src/physics/Integrator.cpp
)

target_link_libraries(
    PhysicsSim
    PRIVATE
    OpenGL::GL
    glfw
    glm::glm
)

target_include_directories(
    PhysicsSim
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)