#ifndef PERENDER_CPERENDERER_H
#define PERENDER_CPERENDERER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include "CPeVulkanRenderer.h"

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

		#define IMGUI_UNLIMITED_FRAME_RATE
#ifdef _DEBUG
#define IMGUI_VULKAN_DEBUG_REPORT
#endif

		/**
		 * @brief Singleton used to setup render libs and render frames.
		*/
		class CPeRenderer
		{

			//Singleton setup
		public:
			vk::CPeVulkanRenderer vulkanRenderer;
		
			/**
			 * @brief Get the instance of the singleton
			 * @return A reference of the instance 
			*/
			static CPeRenderer& getInstance()
			{
				static CPeRenderer instance;
				return instance;
			}
			CPeRenderer(CPeRenderer const&) = delete;
			void operator=(CPeRenderer const&) = delete;
		private:
			CPeRenderer() {};
			~CPeRenderer();
		protected:

			//Methods
		public:

			/**
			* @brief Setup ImGui, GLFW and Vulkan
			* @return 0 if setup finished correctly, 1 otherwise
			*/
			int RenderSetup();
			
			/**
			 * @brief Cleanup to call before closin program
			 * @return 
			*/
			int RenderCleanup();

			/**
			 * @brief ImGui begin frame (call at the start of the frame)
			*/
			void BeginFrame();

			/**
			 * @brief ImGui render frame (call at the end of the frame)
			*/
			void RenderFrame();
		private:
		protected:

		public:
			GLFWwindow* m_window = nullptr;	/// Pointer to the main GLFW window
			ImGuiIO* m_io = nullptr;		/// Pointer to the ImGUI I/O

			//
			//Demo (may need to be cleaned later)
			ImVec4 m_clear_color;		/// ImGUI demo variable
		private:
			ImGui_ImplVulkanH_Window* m_wd = nullptr;
			VkResult m_err;
			


		protected:
		};
	}
}



#endif /* PERENDER_CPERENDERER_H */