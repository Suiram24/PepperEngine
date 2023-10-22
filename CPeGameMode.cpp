#include "CPeGameMode.h"

namespace engine {

	void CPeGameMode::GameStart()
	{

	}

	void CPeGameMode::GameUpdate()
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