cmake_minimum_required(VERSION 3.10.0)
project(gfx_playground VERSION 1.0.0)

add_executable(
    gfx_playground src/config.cpp
    src/main.cpp
    src/triangle_mesh.cpp
    src/material.cpp
    src/utils.cpp
    src/shader_utils.cpp
    dependencies/glad/glad.c
    dependencies/stb_image.h
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_include_directories(gfx_playground PRIVATE dependencies ${GLFW3_INCLUDE_DIR})

target_link_libraries(gfx_playground ${GLFW3_LIBRARY} OpenGL::GL)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/fragment_shader.fx
            ${CMAKE_CURRENT_BINARY_DIR}/fragment_shader.fx
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/vertex_shader.fx
            ${CMAKE_CURRENT_BINARY_DIR}/vertex_shader.fx
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/img/
    ${CMAKE_CURRENT_BINARY_DIR}/img
)