#include "DemoCustomGameMode.h"


namespace pedemo {

	void DrawImGuiInterface()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Begin("Debug");
		//ImGui::Text("Framerate : %.1f", ImGui::GetIO().Framerate());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		//ImGui::Text("DeltaTime : %.3f", ImGui::GetIO().DeltaTime());
		ImGui::End();
	}

	void DemoCustomGameMode::GameStart()
	{
		i = 0;
		forceSystem = &pephy::CPeForceSystem::GetInstance();

		pephy::CPeParticle& particleComp1 = forceSystem->CreateParticleComponent(&entity1);
		pephy::CPeForceAnchoredSpring& anchoredSpring1 = forceSystem->CreateForceAnchoredSpring(pemaths::CPeVector3(0, 0, 2), 1, 1);
		forceSystem->AddForceToParticle(&anchoredSpring1, &particleComp1);

	}

	void DemoCustomGameMode::GameUpdate()
	{
		DrawImGuiInterface();
		static vk::SphereMesh sphere1(*m_renderer);
		//static vk::SphereMesh sphere2(*m_renderer);
		
		//sphere2.SetPos(std::sin(i*0.1), 0, 0);
		i++;

		namespace pecore = engine::core;
		//static pecore::CPeObjectPool<pecore::CPeComponent, 50> pool;
		
		
		sphere1.SetPos(0, 0, entity1.m_transform.GetPosition().GetZ());

	}

	void DemoCustomGameMode::GameEnd()
	{

	}

	



	
}