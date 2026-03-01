#include "CPeGameMode.h"

namespace engine {

	void CPeGameMode::GameStart()
	{

	}

	void CPeGameMode::GameUpdate(float deltaTime)
	{

	}

	void CPeGameMode::FixedUpdate(float deltaTime)
	{
	}

	void CPeGameMode::PostUpdate(float deltaTime)
	{
	}

	void CPeGameMode::GameEnd()
	{

	}

	void CPeGameMode::InitGameMode(GLFWwindow* p_window, vk::CPeVulkanRenderer* p_renderer)
	{
		m_window = p_window;
		m_renderer = p_renderer;
	}


	
}