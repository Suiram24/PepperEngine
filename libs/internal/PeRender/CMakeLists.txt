link_directories(libs/external/Vulkan/Include)
add_library(
	PeRender
	CpeVulkanRenderer.h		CpeVulkanRenderer.cpp
	CPeGraphicalVertex.h	CPeGraphicalVertex.cpp
	CPeGraphicalObjects.h	CPeGraphicalObjects.cpp
	SphereMesh.h			SphereMesh.cpp
	CPeViewManager.h		CPeViewManager.cpp
	CPeCameraController.h	CPeCameraController.cpp
	CPeBluePrints.h
)
target_link_libraries(PeRender "Vulkan::Vulkan")