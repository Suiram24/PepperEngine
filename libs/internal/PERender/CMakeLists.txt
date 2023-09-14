link_directories(libs/external/Vulkan/Include)
add_library(PERender PERender.h PERender.cpp)
target_link_libraries(PERender "Vulkan::Vulkan")