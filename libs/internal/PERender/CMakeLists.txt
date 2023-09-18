link_directories(libs/external/Vulkan/Include)
add_library(PeRender CPeRenderer.h CPeRenderer.cpp)
target_link_libraries(PeRender "Vulkan::Vulkan")