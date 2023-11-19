#include "DemoPhase3.h"


namespace pedemo {

	void DrawImGuiInterface3()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
	}

	void DemoPhase3::GameStart()
	{
		i = 0;
		forceSystem = &pephy::CPeForceSystem::GetInstance();
		colliderSystem = &pephy::CPeCollisionSystem::GetInstance();
		meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();

		LoadLevel();

	}

	void DemoPhase3::GameUpdate()
	{

		DrawImGuiInterface3();

		static float pos[3] = { entity4->m_transform.GetPosition().GetX(), entity4->m_transform.GetPosition().GetY(), entity4->m_transform.GetPosition().GetZ() };
		static float min[3] = { -5,1,-5 };
		static float max[3] = { 5,10,5 };

		static int i;
		++i;

		ImGui::Begin("Controls");

		ImGui::DragFloat3("Sphere position", pos, 0.1, -8, 8, "%.2f");

		ImGui::End();

		entity4->m_transform.SetPosition(pemaths::CPeVector3(pos[0], pos[1], pos[2]));
	}

	void DemoPhase3::GameEnd()
	{

	}


	void DemoPhase3::LoadLevel()
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

				//floorEntities[i][j]->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

				meshRenderSystem->CreateMeshComponent(floorEntities[i][j], *m_renderer, "models/plane.obj", "textures/debug_texture.png");
			}
		}

		entity1 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity2 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity3 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity4 = &engine::CPeGameManager::getInstance().CreateEntity();

		entity1->m_transform.SetPosition(pemaths::CPeVector3(2, 2, -0.1));
		entity2->m_transform.SetPosition(pemaths::CPeVector3(2, 2, -4));
		entity3->m_transform.SetPosition(pemaths::CPeVector3(-1, 2, -1));
		entity4->m_transform.SetPosition(pemaths::CPeVector3(0, 2, 0));

		entity1->m_transform.SetSize(pemaths::CPeVector3(1, 2, 2));
		entity2->m_transform.SetSize(pemaths::CPeVector3(1.5, 2, 1));
		entity3->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));
		entity4->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

		pephy::CPeRigidBody* rigidbodyComp1 = forceSystem->CreateRigidBodyComponent(entity1, 3);
		rigidbodyComp1->SetCubeInertia(1, 2, 2);

		pephy::CPeRigidBody* rigidbodyComp2 = forceSystem->CreateRigidBodyComponent(entity2, 3);
		pephy::CPeRigidBody* rigidbodyComp3 = forceSystem->CreateRigidBodyComponent(entity3, 3/*, 0, 0, pemaths::CPeVector3()*/);
		pephy::CPeParticle* rigidbodyComp4 = forceSystem->CreateParticleComponent(entity4, 0, 0, pemaths::CPeVector3());

		pephy::CPeColliderComponent* colliderComp1 = colliderSystem->CreateColliderComponent(entity1, 0.5);
		pephy::CPeColliderComponent* colliderComp2 = colliderSystem->CreateColliderComponent(entity2, 1);
		pephy::CPeColliderComponent* colliderComp3 = colliderSystem->CreateColliderComponent(entity3, 0.5);
		pephy::CPeColliderComponent* colliderComp4 = colliderSystem->CreateColliderComponent(entity4, 0.5);


		meshRenderSystem->CreateMeshComponent(entity1, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity2, *m_renderer, "models/sphere.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity3, *m_renderer, "models/sphere.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity4, *m_renderer, "models/viking_room.obj", "textures/viking_room.png");

		pephy::CPeForceFree* free1 = forceSystem->CreateForceFree(pemaths::CPeVector3(0.01, 0, 0.01), pemaths::CPeVector3(0, -1, 0));
		pephy::CPeForceFree* free2 = forceSystem->CreateForceFree(pemaths::CPeVector3(-0.01, 0, -0.01), pemaths::CPeVector3(0, 1, 0));


		pephy::CPeForceSpring* spring1 = forceSystem->CreateForceSpring(rigidbodyComp4, 10, 3, pemaths::CPeVector3(1, 0, 0));
		//pephy::CPeForceSpring* spring2 = forceSystem->CreateForceSpring(rigidbodyComp4, 10, 3, pemaths::CPeVector3(1, 0, 0));
		pephy::CPeForceSpring* spring3 = forceSystem->CreateForceSpring(rigidbodyComp4, 10, 3, pemaths::CPeVector3(1,0,0));
		pephy::CPeForceBuoyancy* water = forceSystem->CreateForceBuoyancy(0.5, 0.52, 0, 10);
		pephy::CPeForceDrag* air = forceSystem->CreateForceDrag(1, 2);

		forceSystem->AddForceToParticle(free1, rigidbodyComp2, -1);
		forceSystem->AddForceToParticle(free2, rigidbodyComp2, -1);

		forceSystem->AddForceToParticle(spring1, rigidbodyComp1, -1);
		//forceSystem->AddForceToParticle(spring2, rigidbodyComp2, -1);
		forceSystem->AddForceToParticle(spring3, rigidbodyComp3, -1);

		forceSystem->AddForceToParticle(water, rigidbodyComp1, -1);
		forceSystem->AddForceToParticle(water, rigidbodyComp2, -1);
		forceSystem->AddForceToParticle(water, rigidbodyComp3, -1);
	}




}