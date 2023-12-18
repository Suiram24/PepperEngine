#include "DemoBillard.h"
# define M_PI           3.14159265358979323846


namespace pedemo {

	void DemoBillard::DrawImGuiInterface()
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::SetNextItemWidth(600);
		ImGui::Begin("Debug");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();
	}

	void DemoBillard::GameStart()
	{
		forceSystem = &pephy::CPeForceSystem::GetInstance();
		colliderSystem = &pephy::CPeCollisionSystem::GetInstance();
		meshRenderSystem = &engine::render::CPeMeshRenderSystem::GetInstance();


		LoadLevel();

		m_renderer->SetNearPlan(0.01f);
		m_renderer->SetFarPlan(20.0f);

		controls::CameraController::ChangeCameraPosition(-1, 0.5, -0.5);
		controls::CameraController::ChangeCameraOrientation(0, 0, 0);

		controls::CameraController::ChangeDisplacementSensitivity(0.1f);
		controls::CameraController::ChangeOrientationSensitivity(0.005f);

		controls::CameraController::InitialiseView();

	}

	void DemoBillard::GameUpdate()
	{
		static float angle, power;
		//DrawImGuiInterface();
		ImGui::SetNextItemWidth(600);
		ImGui::Begin("Billard Controls");
		ImGui::SliderAngle("Angle", &angle);
		ImGui::SliderFloat("Power", &power,0,100);
		
		if (ImGui::Button("Shoot"))
		{
			pephy::CPeForceFree* ShootForce = forceSystem->CreateForceFree(pemaths::CPeVector3(cos(((double)angle/360.)*2*M_PI), 0, sin(((double)angle / 360.) * 2 * M_PI)) * power );
			forceSystem->AddForceToParticle(ShootForce, whiteBall->GetComponent<pephy::CPeRigidBody>(), 0.01);
		}

		


		ImGui::End();
		
	}

	void DemoBillard::GameEnd()
	{

	}


	void DemoBillard::LoadLevel()
	{
		SpawnFloor();
		//SpawnStaticBox(pemaths::CPeVector3(-1, 0, 0), pemaths::CPeVector3(0.2, 0.2, 1.2));
		//SpawnStaticBox(pemaths::CPeVector3(1, 0, 0), pemaths::CPeVector3(0.2, 0.2, 1.2));
		/*SpawnStaticBox(pemaths::CPeVector3(0, 0, 0.5), pemaths::CPeVector3(2.2, 0.2, 0.2));
		SpawnStaticBox(pemaths::CPeVector3(0, 0, -0.5), pemaths::CPeVector3(2.2, 0.2, 0.2));*/

		whiteBall = SpawnSphere(pemaths::CPeVector3(-0.5, 0.025, 0), pemaths::CPeVector3(0.05, 0.05, 0.05));

		SpawnSphere(pemaths::CPeVector3(0.1, 0.025, -0.1), pemaths::CPeVector3(0.05, 0.05, 0.05));
		SpawnSphere(pemaths::CPeVector3(0.1, 0.025, 0.1), pemaths::CPeVector3(0.05, 0.05, 0.05));
		SpawnSphere(pemaths::CPeVector3(0, 0.025, 0), pemaths::CPeVector3(0.05, 0.05, 0.05));
		SpawnSphere(pemaths::CPeVector3(0.2, 0.025, -0.15), pemaths::CPeVector3(0.05, 0.05, 0.05));
		SpawnSphere(pemaths::CPeVector3(0.2, 0.025, 0), pemaths::CPeVector3(0.05, 0.05, 0.05));
		SpawnSphere(pemaths::CPeVector3(0.2, 0.025, 0.15), pemaths::CPeVector3(0.05, 0.05, 0.05));
	}


	pecore::CPeEntity* DemoBillard::SpawnSphere(const pemaths::CPeVector3& p_pos, const pemaths::CPeVector3& p_size)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(p_pos);

		entity->m_transform.SetSize(p_size);

		pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 10);

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

		col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, std::max({p_size.GetX(),p_size.GetY(), p_size.GetZ()})));

		return entity;
	}

	void DemoBillard::SpawnStaticBox(const pemaths::CPeVector3& p_pos, const pemaths::CPeVector3& p_size)
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(p_pos);

		entity->m_transform.SetSize(pemaths::CPeVector3(p_size));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, (p_size * 0.5).GetNorm());

		col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, p_size));
	}

	void DemoBillard::SpawnFloor()
	{
		pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

		entity->m_transform.SetPosition(pemaths::CPeVector3(0, 0, 0));

		entity->m_transform.SetSize(pemaths::CPeVector3(2, 1, 1));

		meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/plane.obj", "textures/debug_texture.png");

		pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, 2);

		col->AddPrimitive(colliderSystem->CreatePlaneShape(*entity, pemaths::CPeVector3(0, 1, 0), 0));
	}



}