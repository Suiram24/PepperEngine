#include "DemoDoublePendulum.h"


namespace pedemo {

	void DrawImGuiInterface4()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
	}

	void DemoDoublePendulum::GameStart()
	{
		forceSystem = &pephy::CPeForceSystem::GetInstance();
		colliderSystem = &pephy::CPeCollisionSystem::GetInstance();
		meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();

		LoadLevel();

	}

	void DemoDoublePendulum::GameUpdate()
	{
		DrawImGuiInterface4();
	}

	void DemoDoublePendulum::GameEnd()
	{

	}


	void DemoDoublePendulum::LoadLevel()
	{

		entity1 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity2 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity3 = &engine::CPeGameManager::getInstance().CreateEntity();

		entity1->m_transform.SetPosition(pemaths::CPeVector3(0, 6, 0));
		entity2->m_transform.SetPosition(pemaths::CPeVector3(3.5, 6, 0));
		entity3->m_transform.SetPosition(pemaths::CPeVector3(8.5, 6, 0));

		entity1->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));
		entity2->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));
		entity3->m_transform.SetSize(pemaths::CPeVector3(3, 0.5, 1));

		pephy::CPeRigidBody* rigidbodyComp1 = forceSystem->CreateRigidBodyComponent(entity1, 0, 1, pemaths::CPeVector3(0,0,0));
		pephy::CPeRigidBody* rigidbodyComp2 = forceSystem->CreateRigidBodyComponent(entity2, 1, 1);
		pephy::CPeRigidBody* rigidbodyComp3 = forceSystem->CreateRigidBodyComponent(entity3, 10, 1);

		rigidbodyComp1->SetCubeInertia(1, 1, 1);
		rigidbodyComp2->SetSphereInertia(1);
		rigidbodyComp3->SetCubeInertia(3, 0.5, 1);

		meshRenderSystem->CreateMeshComponent(entity1, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity2, *m_renderer, "models/sphere.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity3, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");


		pephy::CPeForceSpring* spring1 = forceSystem->CreateForceSpring(rigidbodyComp1, 10, 3, pemaths::CPeVector3(-0.5f, 0, 0));
		pephy::CPeForceSpring* spring2 = forceSystem->CreateForceSpring(rigidbodyComp3, 1, 3, pemaths::CPeVector3(0.5f, 0, 0), pemaths::CPeVector3(-1.5f, 0, 0));
;

		forceSystem->AddForceToParticle(spring1, rigidbodyComp2, -1);
		forceSystem->AddForceToParticle(spring2, rigidbodyComp2, -1);
	}




}