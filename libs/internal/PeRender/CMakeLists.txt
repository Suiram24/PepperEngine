link_directories(libs/external/Vulkan/Include)
add_library(PeRender CPeRenderer.h CPeRenderer.cpp CpeVulkanRenderer.h CpeVulkanRenderer.cpp CPeGraphicalVertex.h CPeGraphicalVertex.cpp CPeGraphicalObjects.h CPeGraphicalObjects.cpp CPeBluePrints.h)
target_link_libraries(PeRender "Vulkan::Vulkan")