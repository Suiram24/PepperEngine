#include "DemoPenduleNewton.h"
#include <cmath>

namespace pedemo {

	void DemoPenduleNewton::DrawImGuiInterface()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
	}

	void DemoPenduleNewton::GameStart()
	{
		forceSystem = &pephy::CPeForceSystem::GetInstance();
		colliderSystem = &pephy::CPeCollisionSystem::GetInstance();
		meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();

		LoadLevel();

		world = pecore::CPeWorld();

		vector test = { 2,3 };
		vector test2 = { 8,9 };
		hp defaultHP = { 100,100 };
		hp bossHP = { 50,100 };

		pecore::PeComponentID id = world.GetID<vector>();
		pecore::PeComponentID id2 = world.GetID<vector>();

		pecore::PeEntity e1 = world.CreateEntity();
		world.Add<vector>(e1);
		world.Set<vector>(e1, test);
		bool bTest = world.HasComponent<vector>(e1);
		test2 = *(world.Get<vector>(e1));
		world.Add<ally>(e1);
		test2 = *(world.Get<vector>(e1));

		pecore::PeEntity a1 = world.CreateEntity();
		world.Set<hp>(a1, { 150,150 });
		world.Add<ally>(a1);
		pecore::PeEntity a2 = world.CreateEntity();
		world.Set<hp>(a2, { 100,150 });
		world.Add<ally>(a2);
		pecore::PeEntity e2 = world.CreateEntity();
		world.Set<hp>(e2, { 100,100 });
		world.Add<ennemy>(e2);
		pecore::PeEntity e3 = world.CreateEntity();
		world.Set<hp>(e3, { 50,100 });
		world.Add<ennemy>(e3);
		pecore::PeEntity e4 = world.CreateEntity();
		world.Set<hp>(e4, { 500,500 });
		world.Add<ennemy>(e4);

		printf("Allies:\n");
		std::function<void(hp&, ally&)> allyIt = [](hp& hpComponent, ally& allyComponent)
		{
			printf("HP : %.0f", hpComponent.currentHP);
			printf("/%.0f\n", hpComponent.maxHP);
		};
		std::function<void(hp&, ennemy&)> ennemyIt = [](hp& hpComponent, ennemy& ennemyComponent)
		{
			printf("HP : %.0f", hpComponent.currentHP);
			printf("/%.0f\n", hpComponent.maxHP);
		};
		std::function<void(hp&)> impossibleIT = [](hp& hpComponent)
		{
			printf("HP : %.0f", hpComponent.currentHP);
			printf("/%.0f\n", hpComponent.maxHP);
		};





		world.ForEach(allyIt);
		printf("Ennemies:\n");
		world.ForEach(ennemyIt);
		printf("All:\n");
		world.ForEach(impossibleIT);

		query = world.Build<vector>();
		queryFunction = [](vector& vec)
			{
				vec.y -= 0.98;
				printf("%.2f|", vec.y);
			};
		
	}

	void DemoPenduleNewton::GameUpdate()
	{

		DrawImGuiInterface();
		printf("Vectors y : ");
		query.ForEach(queryFunction);
		printf("\n");
	}

	void DemoPenduleNewton::GameEnd()
	{

	}


	void DemoPenduleNewton::LoadLevel()
	{
		SetupCameraParameters();

		pephy::CPeRigidBody* bar = SpawnStaticBox(0,5,0);

		int count = 3;

		for (int i = -2; i < count; i++)
		{
			pephy::CPeRigidBody* ball = SpawnSphere(i, 1.75, 0);

			pephy::CPeForceAnchoredSpring* spring = forceSystem->CreateForceAnchoredSpring(pemaths::CPeVector3(i, 13, 0), 100, 10, pemaths::CPeVector3(0, 0.5, 0));

			forceSystem->AddForceToParticle(spring, ball);
			
			if (i == count - 1)
			{
				pephy::CPeForceCustomLocal* force = forceSystem->CreateForceCustomLocal(pemaths::CPeVector3(70, 0, 0), pemaths::CPeVector3());
				forceSystem->AddForceToParticle(force, ball, 1);
			}
		}

		//DemoBoxes();
		//DemoSpheres();
	}

	void DemoPenduleNewton::SpawnBox(double p_x, double p_y, double p_z)
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

	pephy::CPeRigidBody* DemoPenduleNewton::SpawnSphere(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

		pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 1e-1);

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, 0.5, 0.999));

		return rigidbodyComp;
	}

	pephy::CPeRigidBody* DemoPenduleNewton::SpawnStaticBox(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(10, 1, 1));

		pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 0, 0.999, pemaths::CPeVector3(0, 0, 0));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, 5);

		col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, pemaths::CPeVector3(10, 1, 1)));

		return rigidbodyComp;
	}

	void DemoPenduleNewton::SpawnFloor()
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(0, 0, 0));

		entity->m_transform.SetSize(pemaths::CPeVector3(100, 1, 100));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/plane.obj", "textures/debug_texture.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, 100);

		col->AddPrimitive(colliderSystem->CreatePlaneShape(*entity, pemaths::CPeVector3(0, 1, 0), 0));
	}

	void DemoPenduleNewton::SpawnStaticSphere(double p_x, double p_y, double p_z)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

		entity->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, 0.5));
	}

	void DemoPenduleNewton::DemoSpheres()
	{
		SpawnFloor();

		for (int i = -2; i < 1; i++)
		{
			for (int j = -2; j < 1; j++)
			{
				SpawnSphere(2 * i + 2, 6, 2 * j + 2);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			SpawnSphere((i % 2) * 0.5, 6 + 2 * i, ((i + 1) % 2) * 0.5);
		}
	}

	void DemoPenduleNewton::DemoBoxes()
	{
		SpawnFloor();

		for (int i = -2; i < 1; i++)
		{
			for (int j = -2; j < 1; j++)
			{
				SpawnBox(2 * i + 2, 6, 2 * j + 2);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			SpawnBox((i % 2) * 0.5, 6 + 2 * i, ((i + 1) % 2) * 0.5);
		}
	}

	void DemoPenduleNewton::SetupCameraParameters()
	{
		m_renderer->SetNearPlan(0.01f);
		m_renderer->SetFarPlan(50.0f);

		controls::CameraController::ChangeCameraPosition(0, 10, -10);
		controls::CameraController::ChangeCameraOrientation(0, 0, 0);

		controls::CameraController::ChangeDisplacementSensitivity(0.1f);
		controls::CameraController::ChangeOrientationSensitivity(0.005f);

		controls::CameraController::InitialiseView();
	}
}