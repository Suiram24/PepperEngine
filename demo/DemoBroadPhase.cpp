#include "DemoBroadPhase.h"
#include <time.h>
#include "../libs/internal/PePhysics/CollisionSystem/CPeKDTree.h"
#include <iostream>

namespace pedemo {

	void DrawImGuiInterfaceBroadPhase()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
	}

	void DemoBroadPhase::GameStart()
	{
		i = 0;
		forceSystem = &pephy::CPeForceSystem::GetInstance();
		//colliderSystem = &pephy::CPeCollisionSystem::GetInstance();
		meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();

		LoadLevel();

	}

	void DemoBroadPhase::GameUpdate()
	{
	}

	void DemoBroadPhase::GameEnd()
	{

	}


	void DemoBroadPhase::LoadLevel()
	{
		std::vector<vk::SphereMesh*> spheres;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				floorEntities[i][j] = &engine::CPeGameManager::getInstance().CreateEntity();
				floorEntities[i][j]->m_transform.SetPosition(pemaths::CPeVector3(i - 5, 0, j - 5));

				forceSystem->CreateParticleComponent(floorEntities[i][j], 0, 0, pemaths::CPeVector3());
				//colliderSystem->CreateColliderComponent(floorEntities[i][j], 0.5);

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
		entity3->m_transform.SetPosition(pemaths::CPeVector3(6, 2, -1));
		entity4->m_transform.SetPosition(pemaths::CPeVector3(0, 2, 0));

		entity1->m_transform.SetSize(pemaths::CPeVector3(1, 2, 2));
		entity2->m_transform.SetSize(pemaths::CPeVector3(1.5, 2, 1));
		entity3->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));
		entity4->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));


		meshRenderSystem->CreateMeshComponent(entity1, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity2, *m_renderer, "models/sphere.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity3, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");
		meshRenderSystem->CreateMeshComponent(entity4, *m_renderer, "models/viking_room.obj", "textures/viking_room.png");

		std::vector<pephy::CPeColliderComponent*> colliders;
		colliders.push_back(entity1->GetComponent<pephy::CPeColliderComponent>());
		colliders.push_back(entity2->GetComponent<pephy::CPeColliderComponent>());
		colliders.push_back(entity3->GetComponent<pephy::CPeColliderComponent>());
		colliders.push_back(entity4->GetComponent<pephy::CPeColliderComponent>());

		// Créer un KD Tree avec la liste de collider en paramètre
		pephy::CPeKDTree broadPhaseTree(pephy::EPeDimension::X, colliders);

		// Checker les pairs
		auto possibleCollisions = broadPhaseTree.GetPossibleCollisions();

		// Print pairs
		for (auto& possibleCollision : possibleCollisions) {
			std::cout << "pair: <";
			if (&possibleCollision.first->GetOwner() == entity1) {
				std::cout << "entity1";
			}
			else if (&possibleCollision.first->GetOwner() == entity2) {
				std::cout << "entity2";
			}
			else if (&possibleCollision.first->GetOwner() == entity3) {
				std::cout << "entity3";
			}
			else if (&possibleCollision.first->GetOwner() == entity4) {
				std::cout << "entity4";
			}
			std::cout << ", ";
			if (&possibleCollision.second->GetOwner() == entity1) {
				std::cout << "entity1";
			}
			else if (&possibleCollision.second->GetOwner() == entity2) {
				std::cout << "entity2";
			}
			else if (&possibleCollision.second->GetOwner() == entity3) {
				std::cout << "entity3";
			}
			else if (&possibleCollision.second->GetOwner() == entity4) {
				std::cout << "entity4";
			}
			std::cout << std::endl;
		}
	}




}