#include "CPeGameManager.h"

namespace engine {

	void CPeGameManager::SetGameMode(CPeGameMode* p_gameMode)
	{
		m_ActiveGameMode = p_gameMode;
	}

	void CPeGameManager::StartGame()
	{
		//
		// Render setup
		if (m_ActiveGameMode == nullptr)
		{
			printf("Error: game cannot start: GameMode no set");
			return;
		}

		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_window = glfwCreateWindow(vk::WIDTH, vk::HEIGHT, "Vulkan", nullptr, nullptr);

		//vk::CPeVulkanRenderer renderer;
		engine::render::CPeImGuiRenderer& imguiRenderer = engine::render::CPeImGuiRenderer::getInstance();
		imguiRenderer.SetupInterface();
		m_renderer.init(m_window);

		//
		// Give the window and renderer to the gamemode
		m_ActiveGameMode->InitGameMode(m_window, &m_renderer);

		


		m_ActiveGameMode->GameStart();

		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
			m_renderer.beginDrawFrame();


			m_ActiveGameMode->GameUpdate();

			PhysicUpdate(ImGui::GetIO().DeltaTime);

			m_renderer.endDrawFrame();
		}

		m_ActiveGameMode->GameEnd();

	}

	void CPeGameManager::PhysicUpdate(double p_deltaTime)
	{
		double totalTime = m_UncomputedTimeLeft + p_deltaTime;
		while (totalTime > m_timeStep)
		{
			m_forceSystem->Update(m_timeStep);
			totalTime -= m_timeStep;
		}

		m_UncomputedTimeLeft = totalTime;

		
	}

	void CPeGameManager::AllocateObjectsPool()
	{
		m_entityPool = new pecore::CPeObjectPool<pecore::CPeEntity, pecore::consts::maxEntityNumber>();
		m_forceSystem->AllocateObjectsPool();
	}

	void CPeGameManager::FreeObjectsPool()
	{
		delete m_entityPool;
		m_forceSystem->FreeObjectsPool();
	}

	pecore::CPeEntity& CPeGameManager::CreateEntity(const pemaths::CPeTransform& p_transform)
	{
		return m_entityPool->Create(p_transform);
	}
	
}

