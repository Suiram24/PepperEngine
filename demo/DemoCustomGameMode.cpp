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

		LoadLevel();

	}

	void DemoCustomGameMode::GameUpdate()
	{
		//static pephy::CPeColliderComponent colliderComp1(*entity1, 0.5);
		//static pephy::CPeColliderComponent colliderComp2(*entity2, 0.5);
		//static pephy::CPeColliderComponent colliderComp3(*entity3, 0.5);

		DrawImGuiInterface();
		static vk::SphereMesh sphere1(*m_renderer);
		static vk::SphereMesh sphere2(*m_renderer);
		static vk::SphereMesh sphere3(*m_renderer);
		static vk::SphereMesh sphere4(*m_renderer);
		static float pos[3] = { entity4->m_transform.GetPosition().GetX(), entity4->m_transform.GetPosition().GetY(), entity4->m_transform.GetPosition().GetZ() };
		static float min[3] = { -5,1,-5 };
		static float max[3] = { 5,10,5 };

		sphere1.SetPos(entity1->m_transform.GetPosition().GetX(), entity1->m_transform.GetPosition().GetY(), entity1->m_transform.GetPosition().GetZ());
		sphere1.SetScale(0.5);

		sphere2.SetPos(entity2->m_transform.GetPosition().GetX(), entity2->m_transform.GetPosition().GetY(), entity2->m_transform.GetPosition().GetZ());
		sphere2.SetScale(1);

		sphere3.SetPos(entity3->m_transform.GetPosition().GetX(), entity3->m_transform.GetPosition().GetY(), entity3->m_transform.GetPosition().GetZ());
		sphere3.SetScale(0.5);

		sphere4.SetPos(entity4->m_transform.GetPosition().GetX(), entity4->m_transform.GetPosition().GetY(), entity4->m_transform.GetPosition().GetZ());
		sphere4.SetScale(0.5);

		//printf("Y positions: %.3f, %.3f, %.3f", entity1->m_transform.GetPosition().GetY(), entity2->m_transform.GetPosition().GetY(), entity3->m_transform.GetPosition().GetY());
		//sphere2.SetPos(std::sin(i*0.1), 0, 0);
		//i++;

		ImGui::Begin("Controls");

		ImGui::DragFloat3("Sphere position", pos,0.1, -8, 8, "%.2f");

		ImGui::End();

		entity4->m_transform.SetPosition(pemaths::CPeVector3(pos[0], pos[1], pos[2]));



	}

	void DemoCustomGameMode::GameEnd()
	{

	}

	
	void DemoCustomGameMode::LoadLevel()
	{
		std::vector<vk::SphereMesh*> spheres;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				floorEntities[i][j] = &engine::CPeGameManager::getInstance().CreateEntity();
				floorEntities[i][j]->m_transform.SetPosition(pemaths::CPeVector3(i - 5, 0, j - 5));

				forceSystem->CreateParticleComponent(floorEntities[i][j], 0, 0, pemaths::CPeVector3());
				colliderSystem->CreateColliderComponent(floorEntities[i][j], 0.5);

				spheres.push_back(new vk::SphereMesh(*m_renderer));
				spheres.back()->SetPos(i - 5, 0, j - 5);
				spheres.back()->SetScale(0.5);
			}
		}

		entity1 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity2 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity3 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity4 = &engine::CPeGameManager::getInstance().CreateEntity();

		entity1->m_transform.SetPosition(pemaths::CPeVector3(2, 2, -0.1));
		entity2->m_transform.SetPosition(pemaths::CPeVector3(-1, 2, -3));
		entity3->m_transform.SetPosition(pemaths::CPeVector3(-1, 2, -1));
		entity4->m_transform.SetPosition(pemaths::CPeVector3(0, 1, 0));

		pephy::CPeParticle* particleComp1 = forceSystem->CreateParticleComponent(entity1, 3);
		pephy::CPeParticle* particleComp2 = forceSystem->CreateParticleComponent(entity2, 3);
		pephy::CPeParticle* particleComp3 = forceSystem->CreateParticleComponent(entity3, 3/*, 0, 0, pemaths::CPeVector3()*/);
		pephy::CPeParticle* particleComp4 = forceSystem->CreateParticleComponent(entity4, 0, 0, pemaths::CPeVector3());

		pephy::CPeColliderComponent* colliderComp1 = colliderSystem->CreateColliderComponent(entity1, 0.5);
		pephy::CPeColliderComponent* colliderComp2 = colliderSystem->CreateColliderComponent(entity2, 1);
		pephy::CPeColliderComponent* colliderComp3 = colliderSystem->CreateColliderComponent(entity3, 0.5);
		pephy::CPeColliderComponent* colliderComp4 = colliderSystem->CreateColliderComponent(entity4, 0.5);

		//colliderSystem->CreateCableBetween(particleComp1, particleComp2, 0.999, 3);
		//colliderSystem->CreateCableBetween(particleComp2, particleComp3, 0.999, 3);
		colliderSystem->CreateCableBetween(particleComp2, particleComp3, 0.999, 3);
		//colliderSystem->CreateRodBetween(particleComp2, particleComp3, 0.999, 3);

		//pephy::CPeForceSpring* spring1 = forceSystem->CreateForceSpring(particleComp2, 10, 3);
		//pephy::CPeForceSpring* spring2 = forceSystem->CreateForceSpring(particleComp3, 10, 3);
		//pephy::CPeForceSpring* spring3 = forceSystem->CreateForceSpring(particleComp1, 10, 3);

		pephy::CPeForceSpring* spring4 = forceSystem->CreateForceSpring(particleComp4, 10, 3);
		pephy::CPeForceBuoyancy* water = forceSystem->CreateForceBuoyancy(0.5, 0.52, 0, 10);
		pephy::CPeForceDrag* air = forceSystem->CreateForceDrag(1, 2);

		//forceSystem->AddForceToParticle(spring1, particleComp1, -1);
		//forceSystem->AddForceToParticle(spring2, particleComp2, -1);
		//forceSystem->AddForceToParticle(spring3, particleComp3, -1);

		forceSystem->AddForceToParticle(spring4, particleComp1, -1);
		forceSystem->AddForceToParticle(spring4, particleComp2, -1);
		//forceSystem->AddForceToParticle(spring4, particleComp3, -1);

		forceSystem->AddForceToParticle(water, particleComp1, -1);
		forceSystem->AddForceToParticle(water, particleComp2, -1);
		forceSystem->AddForceToParticle(water, particleComp3, -1);
	}



	
}