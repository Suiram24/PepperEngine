cmake_minimum_required(VERSION 3.10)
project(PepperEngine)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PepperEngine_VERSION_MAJOR 1)
set(PepperEngine_VERSION_MINOR 0)


add_executable(PepperEngine main.cpp )

configure_file(PEConfig.h.in PEConfig.h)

target_include_directories(PepperEngine PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

add_subdirectory(libs/ImGui)
target_link_libraries(PepperEngine PUBLIC ImGui)
target_include_directories(PepperEngine PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libs/ImGui"
                          )

target_link_libraries(PepperEngine PUBLIC libs/glfw3.lib)
target_include_directories(PepperEngine PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libs/GLFW"
                          )

target_link_libraries(PepperEngine PUBLIC libs/vulkan-1.lib)
target_include_directories(PepperEngine PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libs/Vulkan"
                          )