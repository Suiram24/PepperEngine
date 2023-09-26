#ifndef PERENDER_CPERENDERER_H
#define PERENDER_CPERENDERER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"

#include <stdio.h>          // printf, fprintf
#include <stdlib.h>         // abort



namespace engine 
{
	namespace render {

		/**
		 * @brief Singleton used to setup render libs and render frames.
		*/
		class CPeImGuiRenderer {

			//Singleton setup
		public:
			/**
			 * @brief Get the instance of the singleton
			 * @return A reference of the instance 
			*/
			static CPeImGuiRenderer& getInstance()
			{
				static CPeImGuiRenderer instance;
				return instance;
			}
			CPeImGuiRenderer(CPeImGuiRenderer const&) = delete;
			void operator=(CPeImGuiRenderer const&) = delete;
		private:
			CPeImGuiRenderer()
			{
			}
		protected:

			//Methods
		public:
			void SetupInterface();

			void RenderInterface();
			
		private:
		protected:
		/********************************
		*          Variables            *
		********************************/
		public:
		private:
			ImVec4 clear_color;
			//ImGuiIO& io = io = ImGui::GetIO(); //to retrieve framerate;
			bool startSim = false;
			float force = 0.0f;
			int angle = 0;
			


		protected:
		};
	}
}



#endif /* PERENDER_CPERENDERER_H */