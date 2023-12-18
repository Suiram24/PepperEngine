#include "DemoBunch.h"
#include <cmath>

namespace pedemo {

	void DemoBunch::DrawImGuiInterface()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
	}

	void DemoBunch::GameStart()
	{
		forceSystem = &pephy::CPeForceSystem::GetInstance();
		colliderSystem = &pephy::CPeCollisionSystem::GetInstance();
		meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();

		LoadLevel();

	}

	void DemoBunch::GameUpdate()
	{

		DrawImGuiInterface();

		
	}

	void DemoBunch::GameEnd()
	{

	}


	void DemoBunch::LoadLevel()
	{
		SetupCameraParameters();
		SpawnFloor();
		entities.push_back(SpawnStaticBox(0, 6, 0));

		entities.push_back(SpawnSphere(4, 7, 4));   // 1
		entities.push_back(SpawnSphere(4, 8, 0));   // 2
		entities.push_back(SpawnSphere(4, 6, -4));  // 3
		entities.push_back(SpawnSphere(0, 5, -4));  // 4
		//entities.push_back(SpawnBox(-4, 8, -4)); // 5
		//entities.push_back(SpawnBox(-4, 8, 0));  // 6
		//entities.push_back(SpawnBox(-4, 7, 4));  // 7
		//entities.push_back(SpawnBox(0, 6, 4));   // 8

		pephy::CPeForceAnchoredSpring* spring = forceSystem->CreateForceAnchoredSpring(pemaths::CPeVector3(0, 5.5f, 0), 10, 1);
		for (int i = 1; i < entities.size(); ++i) {
			forceSystem->AddForceAtPoint(spring, entities[i]->GetComponent<pephy::CPeRigidBody>(), pemaths::CPeVector3(0, 0.5f, 0));
		}


	}

	pecore::CPeEntity* DemoBunch::SpawnBox(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();
		
		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));
		
		entity->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));

		//pemaths::CPeQuaternion rot = pemaths::CPeQuaternion(pemaths::CPeVector3(1, 0, 0), 0.785398163397448309616);
		//entity3->m_transform.SetOrientation(rot);

		pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 1e-1);

		rigidbodyComp->SetCubeInertia(1, 1, 1);

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");
		
		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, pemaths::CPeVector3(1, 1, 1)));

		return entity;
	}

	pecore::CPeEntity* DemoBunch::SpawnSphere(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

		pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 1e-1);

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, 0.5));

		return entity;
	}

	pecore::CPeEntity* DemoBunch::SpawnStaticBox(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x,p_y,p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, pemaths::CPeVector3(1, 1, 1)));

		return entity;
	}

	pecore::CPeEntity* DemoBunch::SpawnFloor()
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(0, 0, 0));

		entity->m_transform.SetSize(pemaths::CPeVector3(100, 1, 100));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/plane.obj", "textures/debug_texture.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, 100);

		col->AddPrimitive(colliderSystem->CreatePlaneShape(*entity, pemaths::CPeVector3(0, 1, 0), 0));

		return entity;
	}

	pecore::CPeEntity* DemoBunch::SpawnStaticSphere(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, 0.5));

		return entity;
	}

	void DemoBunch::SetupCameraParameters()
	{
		m_renderer->SetNearPlan(0.01f);
		m_renderer->SetFarPlan(50.0f);

		controls::CameraController::ChangeCameraPosition(-5, 10, -5);
		controls::CameraController::ChangeCameraOrientation(0, 0, 0);

		controls::CameraController::ChangeDisplacementSensitivity(0.1f);
		controls::CameraController::ChangeOrientationSensitivity(0.005f);

		controls::CameraController::InitialiseView();
	}
}