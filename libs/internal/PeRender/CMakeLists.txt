link_directories(libs/external/Vulkan/Include)
add_library(
	PeRender
	CPeMeshComponent.h		CPeMeshComponent.cpp
	CPeMeshRenderSystem.h	CPeMeshRenderSystem.cpp
	CpeVulkanRenderer.h		CpeVulkanRenderer.cpp
	CPeGraphicalVertex.h	CPeGraphicalVertex.cpp
	CPeGraphicalObjects.h	CPeGraphicalObjects.cpp
	CPeTexture.h			CPeTexture.cpp
	SphereMesh.h			SphereMesh.cpp
	PlaneMesh.h				PlaneMesh.cpp
	CPeViewManager.h		CPeViewManager.cpp
	CPeCameraController.h	CPeCameraController.cpp
	CPeBluePrints.h
)
target_link_libraries(PeRender "Vulkan::Vulkan")