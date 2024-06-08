#ifndef PEENGINE_CPEGAMEMANAGER_H
#define PEENGINE_CPEGAMEMANAGER_H

#include "libs/internal/PeRender/PeRender.h"
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
		* @brief The class that will manage the gameloop of a given gamemode
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
			m_forceSystem = &engine::physics::CPeForceSystem::GetInstance();
			m_collisionSystem = &engine::physics::CPeCollisionSystem::GetInstance();
			m_meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();
			AllocateObjectsPool();		
		}

		/**
		 * @brief Set the Gamemode of the Game manager
		*/
		void SetGameMode(CPeGameMode* p_gameMode);

		/**
		 * @brief Start the game loop. The gamemode must be set. 
		*/
		void StartGame();

		/**
		 * @brief Create an entity in the game world and return a reference.
		*/
		pecore::CPeEntity& CreateEntity(const pemaths::CPeTransform& p_transform = pemaths::CPeTransform());

	protected:
		void SetupCameraParameters();
	private:

		void PhysicUpdate(double p_deltaTime);
		void CollisionUpdate(double m_timeStep);

		void AllocateObjectsPool();
		void FreeObjectsPool();

	public:
	protected:
		vk::CPeVulkanRenderer m_renderer;
	private:

		CPeGameMode* m_ActiveGameMode;
		GLFWwindow* m_window;
		engine::physics::CPeForceSystem* m_forceSystem;
		engine::physics::CPeCollisionSystem* m_collisionSystem;
		engine::render::CPeMeshRenderSystem* m_meshRenderSystem;

	
		//
		// Physics
		double m_UncomputedTimeLeft;
		const double m_timeStep = double(1)/consts::physicsFrameRate;

		pecore::CPeObjectPool<pecore::CPeEntity, pecore::consts::maxEntityNumber>* m_entityPool;
		
	};
	
}

#endif /* PEENGINE_CPEGAMEMANAGER_H */