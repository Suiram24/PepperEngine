#ifndef PEENGINE_CPEGAMEMANAGER_H
#define PEENGINE_CPEGAMEMANAGER_H

#include "libs/internal/PeRender/CPeVulkanRenderer.h"
//#include "libs/internal/PeMaths/PeMaths.h"
#include "libs/internal/PePhysics/PePhysics.h"

#include "CPeGameMode.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>


namespace engine 
{

	namespace consts
	{
		const int physicsFrameRate = 300; //Physics fps
	}
	
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
			, m_UncomputedTimeLeft(0)
		{
			
		}

		void SetGameMode(CPeGameMode* p_gameMode);

		void StartGame();

	protected:
	private:

		void PhysicUpdate(double p_deltaTime);

	public:
	protected:
	private:

		CPeGameMode* m_ActiveGameMode;
		GLFWwindow* m_window;
		vk::CPeVulkanRenderer m_renderer;
		engine::physics::CPeForceSystem* m_forceSystem;

	
		//
		// Physics
		double m_UncomputedTimeLeft;
		const double m_timeStep = double(1)/consts::physicsFrameRate;
		
	};
	
}

#endif /* PEENGINE_CPEGAMEMANAGER_H */