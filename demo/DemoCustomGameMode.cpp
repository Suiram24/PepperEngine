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
		colliderSystem = &pephy::CPeCollisionSystem::GetInstance();

		textures.push_back(new vk::CPeTexture(*m_renderer, "textures/debug_texture.png"));
		textures.push_back(new vk::CPeTexture(*m_renderer, "textures/minecraft.png"));

		entity1 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity2 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity3 = &engine::CPeGameManager::getInstance().CreateEntity();

		entity1->m_transform.SetPosition(pemaths::CPeVector3(-5, 10, 0));
		entity2->m_transform.SetPosition(pemaths::CPeVector3(-5, 1, 0));
		entity3->m_transform.SetPosition(pemaths::CPeVector3(-5, 0, 0));

		pephy::CPeParticle& particleComp1 = forceSystem->CreateParticleComponent(entity1);
		pephy::CPeParticle& particleComp2 = forceSystem->CreateParticleComponent(entity2);
		pephy::CPeParticle& particleComp3 = forceSystem->CreateParticleComponent(entity3, 0, 0, pemaths::CPeVector3());

		//Setup ground
		std::vector<vk::PlaneMesh*> planes;
		float centerX = -5.0f, centerY = -0.5f, centerZ = 0.0f;
		float gridSize = 7;
		for (int i = 0; i < gridSize; ++i) {
			for (int j = 0; j < gridSize; ++j) {
				planes.push_back(new vk::PlaneMesh(*m_renderer, *textures[1]));
				planes.back()->SetPos((j - gridSize / 2) * 1 + centerX, centerY, (i - gridSize / 2) * 1 + centerZ);
			}
		}
		//pephy::CPeForceAnchoredSpring& anchoredSpring1 = forceSystem->CreateForceAnchoredSpring(pemaths::CPeVector3(0, 0, 1), 1000, 0.5);
		//forceSystem->AddForceToParticle(&anchoredSpring1, &particleComp1);

	}

	void DemoCustomGameMode::GameUpdate()
	{
		static pephy::CPeColliderComponent colliderComp1(*entity1, 0.5);
		static pephy::CPeColliderComponent colliderComp2(*entity2, 0.5);
		static pephy::CPeColliderComponent colliderComp3(*entity3, 0.5);

		DrawImGuiInterface();
		static vk::SphereMesh sphere1(*m_renderer, *textures[0]);
		static vk::SphereMesh sphere2(*m_renderer, *textures[0]);
		static vk::SphereMesh sphere3(*m_renderer, *textures[0]);
		

		//if (entity1->m_transform.GetPosition().GetY() < 0)
		//{
		//	entity1->GetComponent<pephy::CPeParticle>()->SetVelocity(pemaths::CPeVector3(0,- entity1->GetComponent<pephy::CPeParticle>()->GetVelocity().GetY(), 0));
		//}
		//if (entity2->m_transform.GetPosition().GetY() < 0)
		//{
		//	entity2->GetComponent<pephy::CPeParticle>()->SetVelocity(pemaths::CPeVector3(0, -entity1->GetComponent<pephy::CPeParticle>()->GetVelocity().GetY(), 0));
		//}


		sphere1.SetPos(entity1->m_transform.GetPosition().GetX(), entity1->m_transform.GetPosition().GetY(), entity1->m_transform.GetPosition().GetZ());
		sphere1.SetScale(0.5);

		sphere2.SetPos(entity2->m_transform.GetPosition().GetX(), entity2->m_transform.GetPosition().GetY(), entity2->m_transform.GetPosition().GetZ());
		sphere2.SetScale(0.5);

		sphere3.SetPos(entity3->m_transform.GetPosition().GetX(), entity3->m_transform.GetPosition().GetY(), entity3->m_transform.GetPosition().GetZ());
		sphere3.SetScale(0.5);

		//printf("Y positions: %.3f, %.3f, %.3f", entity1->m_transform.GetPosition().GetY(), entity2->m_transform.GetPosition().GetY(), entity3->m_transform.GetPosition().GetY());
		//sphere2.SetPos(std::sin(i*0.1), 0, 0);
		i++;

		//namespace pecore = engine::core;
		////static pecore::CPeObjectPool<pecore::CPeComponent, 50> pool;
		//
		//
		//sphere1.SetPos(0, 0, entity1->m_transform.GetPosition().GetZ());
		//sphere1.SetScale(0.25);

	}

	void DemoCustomGameMode::GameEnd()
	{

	}

	



	
}