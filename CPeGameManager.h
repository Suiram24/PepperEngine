#ifndef PEENGINE_CPEGAMEMANAGER_H
#define PEENGINE_CPEGAMEMANAGER_H

#include "libs/internal/PeRender/CPeVulkanRenderer.h"
//#include "libs/internal/PeMaths/PeMaths.h"
//#include "libs/internal/PePhysics/PePhysics.h"

#include "CPeGameMode.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>


namespace engine {
	
	/**
		* @brief A class for basic components regarding the physics of a 3D elements.
	*/
	class CPeGameManager
	{

	public:
		//
		// Singleton setup
		static CPeGameManager& getInstance()
		{
			static CPeGameManager instance;
			return instance;
		}
		CPeGameManager(CPeGameManager const&) = delete;
		void operator=(CPeGameManager const&) = delete;

		CPeGameManager()
			: m_ActiveGameMode(nullptr)
			, m_window(nullptr)
			//, m_renderer()
		{
			
		}

		void SetGameMode(CPeGameMode* p_gameMode);

		void StartGame();

	protected:
	private:

	public:
	protected:
	private:

		CPeGameMode* m_ActiveGameMode;
		GLFWwindow* m_window;
		vk::CPeVulkanRenderer m_renderer;

	

	};
	
}

#endif /* PEENGINE_CPEGAMEMANAGER_H */