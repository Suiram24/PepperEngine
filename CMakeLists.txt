cmake_minimum_required(VERSION 3.10)
project(PepperEngine)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PepperEngine_VERSION_MAJOR 0)
set(PepperEngine_VERSION_MINOR 1)


# GLFW
set(GLFW_DIR libs/external/GLFW/glfw-3.3.8) # Set this to point to an up-to-date GLFW repo
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
set(IMGUI_DIR libs/external/ImGui)
include_directories(${IMGUI_DIR})

# glm
set(GLM_DIR libs/external/glm)
include_directories(${GLM_DIR})

# stb
set(STB_DIR libs/external/stb-master)
include_directories(${STB_DIR})

# tinyobj loader
set(TINYOBJ_L_DIR libs/external/tinyobjloader-release)
include_directories(${TINYOBJ_L_DIR})

# Use vulkan headers from glfw:
include_directories(${GLFW_DIR}/deps)

#PERender
add_subdirectory(libs/internal/PeRender)
add_subdirectory(libs/internal/PeMaths)
add_subdirectory(libs/internal/PePhysics)
set(LIBRARIES ${LIBRARIES} PeRender PeMaths PePhysics)



file(GLOB sources *.cpp)

add_executable(PepperEngine ${sources} ${IMGUI_DIR}/imgui_impl_glfw.cpp  ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp)
target_link_libraries(PepperEngine ${LIBRARIES})
target_compile_definitions(PepperEngine PUBLIC -DImTextureID=ImU64)

# Compile shaders
if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
else()
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin32/glslangValidator.exe")
endif()

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "shaders/*.frag"
    "shaders/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(PepperEngine Shaders)

add_custom_command(TARGET PepperEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:PepperEngine>/shaders/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:PepperEngine>/shaders"
)

# Add Obj and pictures

file(GLOB_RECURSE OBJ_FILES
    "models/*.obj"
    "models/*.fbx"
)

file(GLOB_RECURSE TEXTURE_FILES
    "textures/*.png"
    "textures/*.jpeg"
    "textures/*.jpg"
)

foreach(FILE ${OBJ_FILES})
    get_filename_component(FILE_NAME ${FILE} NAME)
    configure_file(${FILE} ${CMAKE_CURRENT_BINARY_DIR}/models/${FILE_NAME} COPYONLY)
endforeach(FILE)

foreach(FILE ${TEXTURE_FILES})
    get_filename_component(FILE_NAME ${FILE} NAME)
    configure_file(${FILE} ${CMAKE_CURRENT_BINARY_DIR}/textures/${FILE_NAME} COPYONLY)
endforeach(FILE)