#include "DemoCollisionSystem.h"
#include <cmath>

namespace pedemo {

	void DemoCollisionSystem::DrawImGuiInterface()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
	}

	void DemoCollisionSystem::GameStart()
	{
		forceSystem = &pephy::CPeForceSystem::GetInstance();
		colliderSystem = &pephy::CPeCollisionSystem::GetInstance();
		meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();

		LoadLevel();

	}

	void DemoCollisionSystem::GameUpdate()
	{

		DrawImGuiInterface();

		
	}

	void DemoCollisionSystem::GameEnd()
	{

	}


	void DemoCollisionSystem::LoadLevel()
	{
		SpawnFloor();

		for (int i = -2; i < 2; i++)
		{
			for (int j = -2; j < 2; j++)
			{
				//SpawnSphere(2 * i, 6, 2 * j);
				//SpawnBox(2 * i, 10, 2 * j);
				//SpawnStaticBox(2*i, 0, 2*j);
			}
		}
		//SpawnStaticBox(0, 2, 0);

		//SpawnStaticBox(0, 0, 0);
		//SpawnBox(0, 3, 0);
		SpawnSphere(0.5, 6, 0);
		SpawnSphere(0, 3, 0);
	}

	void DemoCollisionSystem::SpawnBox(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();
		
		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));
		
		entity->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));

		//pemaths::CPeQuaternion rot = pemaths::CPeQuaternion(pemaths::CPeVector3(1, 0, 0), 0.785398163397448309616);
		//entity3->m_transform.SetOrientation(rot);

		pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 1e-12);

		rigidbodyComp->SetCubeInertia(1, 1, 1);

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");
		
		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, pemaths::CPeVector3(1, 1, 1)));
	}

	void DemoCollisionSystem::SpawnSphere(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

		pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 1e-12);

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, 0.5));
	}

	void DemoCollisionSystem::SpawnStaticBox(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x,p_y,p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, pemaths::CPeVector3(1, 1, 1)));
	}

	void DemoCollisionSystem::SpawnFloor()
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(0, 0, 0));

		entity->m_transform.SetSize(pemaths::CPeVector3(100, 1, 100));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/plane.obj", "textures/debug_texture.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, 100);

		col->AddPrimitive(colliderSystem->CreatePlaneShape(*entity, pemaths::CPeVector3(0, 1, 0), 0));
	}



}