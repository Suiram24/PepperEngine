#include "DemoCollisionSystem.h"


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

		entity1 = &engine::CPeGameManager::getInstance().CreateEntity();
		//entity2 = &engine::CPeGameManager::getInstance().CreateEntity();
		entity3 = &engine::CPeGameManager::getInstance().CreateEntity();

		entity1->m_transform.SetPosition(pemaths::CPeVector3(0, 0, 0));
		//entity2->m_transform.SetPosition(pemaths::CPeVector3(0, 3, 0));
		entity3->m_transform.SetPosition(pemaths::CPeVector3(0, 6, 0));

		entity1->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));
		//entity2->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));
		entity3->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));
		pemaths::CPeQuaternion rot = pemaths::CPeQuaternion(pemaths::CPeVector3(1, 0, 0), 3.14 / 4);
		entity3->m_transform.SetOrientation(rot);

		//pephy::CPeRigidBody* rigidbodyComp1 = forceSystem->CreateRigidBodyComponent(entity1, 0, 0.999, pemaths::CPeVector3(0,0,0));
		//pephy::CPeRigidBody* rigidbodyComp2 = forceSystem->CreateRigidBodyComponent(entity2, 50);
		pephy::CPeRigidBody* rigidbodyComp3 = forceSystem->CreateRigidBodyComponent(entity3, 10000);

		rigidbodyComp3->SetCubeInertia(1, 1, 1);
		//rigidbodyComp2->SetSphereInertia(1);
		//rigidbodyComp3->SetSphereInertia(1);

		meshRenderSystem->CreateMeshComponent(entity1, *m_renderer, "models/sphere.obj", "textures/viking_room.png");
		//meshRenderSystem->CreateMeshComponent(entity2, *m_renderer, "models/sphere.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity3, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col1 = colliderSystem->CreateColliderComponent(*entity1, 1);
		//pephy::CPeColliderComponent* col2 = colliderSystem->CreateColliderComponent(*entity2, 1);
		pephy::CPeColliderComponent* col3 = colliderSystem->CreateColliderComponent(*entity3, sqrt(3));

		//pephy::CPeSpherePrimitiveShape(entity1, 1)

		col1->AddPrimitive(colliderSystem->CreateSphereShape(*entity1, 1));
		//col2->AddPrimitive(colliderSystem->CreateSphereShape(*entity2, 1));
		col3->AddPrimitive(colliderSystem->CreateBoxShape(*entity3, pemaths::CPeVector3(1,1,1)));


		//pephy::CPeForceSpring* spring1 = forceSystem->CreateForceSpring(rigidbodyComp1, 10, 3, pemaths::CPeVector3(-0.5f, 0, 0));
		//pephy::CPeForceSpring* spring2 = forceSystem->CreateForceSpring(rigidbodyComp3, 1, 3, pemaths::CPeVector3(0.5f, 0, 0), pemaths::CPeVector3(-1.5f, 0, 0));
;

		//forceSystem->AddForceToParticle(spring1, rigidbodyComp2, -1);
		//forceSystem->AddForceToParticle(spring2, rigidbodyComp2, -1);
	}




}