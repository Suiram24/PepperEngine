#ifndef PEENGINE_CPEGAMEMODE_H
#define PEENGINE_CPEGAMEMODE_H

#include "libs/internal/PeRender/CPeVulkanRenderer.h"


#include <GLFW/glfw3.h>

namespace engine {
	
	/**
		* @brief A class for basic components regarding the physics of a 3D elements.
	*/
	class CPeGameMode
	{
		friend class CPeGameManager;
	public:
		CPeGameMode()
			: m_window(nullptr)
			, m_renderer(nullptr)
		{
		}

		/**
		 * @brief Function called once at the start of the game
		*/
		virtual void GameStart();

		/**
		 * @brief Function called once every frame. Put your game logic here.
		*/
		virtual void GameUpdate();

		/**
		 * @brief Function called once at the end of the game
		*/
		virtual void GameEnd();
	protected:
	private:

		/**
			 * @brief Allow the game manager to give usefull pointers to the GameMode. Do not call this function if you aren't working on CPeGameManager.
			 * @param p_window GLFW Window pointer to pass
			 * @param p_renderer CPeVulkanRenderer pointer to pass
			*/
		virtual void InitGameMode(GLFWwindow* p_window, vk::CPeVulkanRenderer* p_renderer) final;


	public:
	protected:
		GLFWwindow* m_window;
		vk::CPeVulkanRenderer* m_renderer;
	private:

	};
	
}

#endif /* PEENGINE_CPEGAMEMODE_H */