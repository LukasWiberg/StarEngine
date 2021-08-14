cmake_minimum_required(VERSION 3.20)
project(StarEngine)

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(StarEngine)

target_link_directories(StarEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")
target_link_directories(StarEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glm/glm")