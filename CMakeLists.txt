cmake_minimum_required(VERSION 3.10)
project(PepperEngine)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PepperEngine_VERSION_MAJOR 1)
set(PepperEngine_VERSION_MINOR 0)


#add_executable(PepperEngine main.cpp )

#configure_file(PEConfig.h.in PEConfig.h)
#
#target_include_directories(PepperEngine PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           )
#
#add_subdirectory(libs/ImGui)
#target_link_libraries(PepperEngine PUBLIC ImGui)
#target_include_directories(PepperEngine PUBLIC
#                          "${PROJECT_BINARY_DIR}"
#                          "${PROJECT_SOURCE_DIR}/libs/ImGui"
#                          )
#
#target_link_libraries(PepperEngine PUBLIC libs/glfw3.lib)
#target_include_directories(PepperEngine PUBLIC
#                          "${PROJECT_BINARY_DIR}"
#                          "${PROJECT_SOURCE_DIR}/libs/GLFW"
#                          )
#
#target_link_libraries(PepperEngine PUBLIC libs/vulkan-1.lib)
#target_include_directories(PepperEngine PUBLIC
#                          "${PROJECT_BINARY_DIR}"
#                          "${PROJECT_SOURCE_DIR}/libs/Vulkan"
#                          )
#
#target_include_directories(PepperEngine PUBLIC "%VULKAN_SDK%/include")
#target_include_directories(PepperEngine PUBLIC "libs/GLFW/include") 

# GLFW
set(GLFW_DIR "D:/Program Files/GLFW/glfw-3.3.8") # Set this to point to an up-to-date GLFW repo
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include)

# Libraries
find_package(Vulkan REQUIRED)
#find_library(VULKAN_LIBRARY
  #NAMES vulkan vulkan-1)
#set(LIBRARIES "glfw;${VULKAN_LIBRARY}")
set(LIBRARIES "glfw;Vulkan::Vulkan")

# Dear ImGui
set(IMGUI_DIR libs/ImGui)
include_directories(${IMGUI_DIR})

# Use vulkan headers from glfw:
include_directories(${GLFW_DIR}/deps)

file(GLOB sources *.cpp)

add_executable(PepperEngine ${sources} ${IMGUI_DIR}/imgui_impl_glfw.cpp ${IMGUI_DIR}/imgui_impl_vulkan.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp)
target_link_libraries(PepperEngine ${LIBRARIES})
target_compile_definitions(PepperEngine PUBLIC -DImTextureID=ImU64)
