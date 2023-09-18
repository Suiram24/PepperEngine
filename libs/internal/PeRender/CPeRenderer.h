

#ifndef PERENDER_CPERENDERER_H
#define PERENDER_CPERENDERER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

#include <stdio.h>          // printf, fprintf
#include <stdlib.h>         // abort

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>



namespace engine 
{
	namespace render
	{

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN

		//#define IMGUI_UNLIMITED_FRAME_RATE
#ifdef _DEBUG
#define IMGUI_VULKAN_DEBUG_REPORT
#endif
		namespace vk 
		{
			// Data
			static VkAllocationCallbacks* g_Allocator = nullptr;
			static VkInstance               g_Instance = VK_NULL_HANDLE;
			static VkPhysicalDevice         g_PhysicalDevice = VK_NULL_HANDLE;
			static VkDevice                 g_Device = VK_NULL_HANDLE;
			static uint32_t                 g_QueueFamily = (uint32_t)-1;
			static VkQueue                  g_Queue = VK_NULL_HANDLE;
			static VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
			static VkPipelineCache          g_PipelineCache = VK_NULL_HANDLE;
			static VkDescriptorPool         g_DescriptorPool = VK_NULL_HANDLE;

			static ImGui_ImplVulkanH_Window g_MainWindowData;
			static int                      g_MinImageCount = 2;
			static bool                     g_SwapChainRebuild = false;
		}


		class CPeRenderer
		{

			//Singleton setup
		public:
			static CPeRenderer& getInstance()
			{
				static CPeRenderer instance;
				return instance;
			}
			CPeRenderer(CPeRenderer const&) = delete;
			void operator=(CPeRenderer const&) = delete;
		private:
			CPeRenderer()
			{
			}
		protected:

			//Methods
		public:
			// Setup ImGui, GLFW and Vulkan
			int RenderSetup();
			// Cleanup to call before closin program
			int RenderCleanup();

			//ImGui begin frame (call at the start of the frame)
			void BeginFrame();
			//ImGui render frame (call at the end of the frame)
			void RenderFrame();
		private:
		protected:

		public:
			GLFWwindow* m_window = nullptr;
			ImGuiIO* m_io = nullptr;

			//
			//Demo (may need to be cleaned later)
			ImVec4 m_clear_color;
			bool m_show_demo_window;	//description
			bool m_show_another_window;
		private:
			ImGui_ImplVulkanH_Window* m_wd = nullptr;
			VkResult m_err;
			


		protected:
		};
	}
}



#endif /* PERENDER_CPERENDERER_H */