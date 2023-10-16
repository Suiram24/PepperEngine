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
		m_renderer.init(m_window, &imguiRenderer);

		//
		// Give the window and renderer to the gamemode
		m_ActiveGameMode->InitGameMode(m_window, &m_renderer);


		m_ActiveGameMode->GameStart();

		while (!glfwWindowShouldClose(m_window))
		{
			m_ActiveGameMode->GameUpdate();

			glfwPollEvents();
			m_renderer.drawFrame();

		}

		m_ActiveGameMode->GameEnd();

	}


	
}