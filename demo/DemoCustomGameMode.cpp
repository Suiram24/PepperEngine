#include "DemoCustomGameMode.h"

namespace pedemo {

	void DemoCustomGameMode::GameStart()
	{
		i = 0;

	}

	void DemoCustomGameMode::GameUpdate()
	{
		static vk::SphereMesh sphere1(*m_renderer);
		static vk::SphereMesh sphere2(*m_renderer);
		sphere1.SetPos(0, 0, std::sin(i * 0.1));
		sphere2.SetPos(std::sin(i*0.1), 0, 0);
		i++;

	}

	void DemoCustomGameMode::GameEnd()
	{

	}



	
}