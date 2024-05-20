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

		forceSystem->InitSystems(world);

		AnchorPoint = new vk::ModelWatcher(*m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");
		Sphere = new vk::ModelWatcher(*m_renderer, "models/sphere.obj", "textures/viking_room.png");

		printf("Game start");

		SetupCameraParameters();

		//world = flecs::world();

		//auto e = world.entity("e1");
		//e.set<Position>({ pemaths::CPeVector3()})
		// .set<Velocity>({ pemaths::CPeVector3() })
		// .set<Acceleration>({ pemaths::CPeVector3(0,0.1,0) })
		// .set<ForceReceiver>({ pemaths::CPeVector3(0,1,1) })
		// .set<Mass>({ 1. });

		//world.entity("e2")
		//	.set<Position>({ pemaths::CPeVector3() })
		//	.set<Velocity>({ pemaths::CPeVector3() })
		//	.set<Acceleration>({ pemaths::CPeVector3(0,0.1,0) })
		//	.set<Mass>({ 1. });

		//world.entity("e3")
		//	.set<Position>({ pemaths::CPeVector3() })
		//	.set<Velocity>({ pemaths::CPeVector3() })
		//	.set<Acceleration>({ pemaths::CPeVector3(0,0.1,0) })
		//	.set<Mass>({ 1. })
		//	.set<ParticleCustomValues>({ pemaths::CPeVector3(0,-10,0),0.99 });

		//world.entity("e4")
		//	.set<Position>({ pemaths::CPeVector3() })
		//	.set<Velocity>({ pemaths::CPeVector3(3,0,0) })
		//	.set<Mass>({ 1. })
		//	.set<ParticleCustomValues>({ pemaths::CPeVector3(0,-10,0),0.99 })
		//	.set<ForceReceiver>({ pemaths::CPeVector3(0,0,0) });


		world.entity("anchor")
			.set<Position>({ pemaths::CPeVector3() });

		pemaths::CPeMatrix3 sphereInertia;
		pephy::CPeRigidBody::ComputeSphereInertia(sphereInertia, 1, 10);

		world.entity("sphere")
			.set<Position>({ pemaths::CPeVector3(0,-0.5,0) })
			.set<Rotation>({ pemaths::CPeQuaternion(1,0,0,0) })
			.set<Velocity>({ pemaths::CPeVector3(-5,0,0) })
			.set<Acceleration>({ pemaths::CPeVector3() })
			.set<Mass>({ 0.1})
			.set<AngularVelocity>({ pemaths::CPeVector3() })
			.set<ParticleCustomValues>({ pemaths::CPeVector3(0,-10,0), 0.999 })
			.set<ForceReceiver>({ pemaths::CPeVector3() })
			.set<AngularAcceleration>({ pemaths::CPeVector3() })
			.set<AnchoredSpring>({ pemaths::CPeVector3(0,3,0), pemaths::CPeVector3(0.0,0.5,0), 100,2 })
			.set<RigidBody>({ pemaths::CPeVector3(), sphereInertia,0.999 })
;
			
		pemaths::CPeMatrix4 peTMatrix;
		pemaths::CPeTransform::ComputeMatrixFromTransform(peTMatrix, pemaths::CPeVector3(0, 3, 0));

		glm::mat4 glmTMatrix = glm::mat4(
			peTMatrix.Get(0, 0), peTMatrix.Get(1, 0), peTMatrix.Get(2, 0), 0,
			peTMatrix.Get(0, 1), peTMatrix.Get(1, 1), peTMatrix.Get(2, 1), 0,
			peTMatrix.Get(0, 2), peTMatrix.Get(1, 2), peTMatrix.Get(2, 2), 0,
			peTMatrix.Get(0, 3), peTMatrix.Get(1, 3), peTMatrix.Get(2, 3), 1
		);

		AnchorPoint->SetTransformMatrix(glmTMatrix);
		particleQuery = world.query< const Position, const Rotation, const RigidBody>();
	}

	void DemoPenduleNewton::GameUpdate()
	{

		DrawImGuiInterface();
		printf("Particle count : %i\n", particleQuery.count());
		
		//Update mesh
		particleQuery.each([](flecs::entity e, const Position& p, const Rotation& r, const RigidBody& a)
			{
				printf("Particle %s position : %.3f \n", e.name().c_str(), p.m_position.GetY());
				
			});
		
		pemaths::CPeVector3 pos = world.lookup("sphere").get<Position>()->m_position;
		pemaths::CPeQuaternion rot = world.lookup("sphere").get<Rotation>()->m_rotation;

		pemaths::CPeMatrix4 peTMatrix;
		pemaths::CPeTransform::ComputeMatrixFromTransform(peTMatrix, pos, rot);

		glm::mat4 glmTMatrix = glm::mat4(
			peTMatrix.Get(0, 0), peTMatrix.Get(1, 0), peTMatrix.Get(2, 0), 0,
			peTMatrix.Get(0, 1), peTMatrix.Get(1, 1), peTMatrix.Get(2, 1), 0,
			peTMatrix.Get(0, 2), peTMatrix.Get(1, 2), peTMatrix.Get(2, 2), 0,
			peTMatrix.Get(0, 3), peTMatrix.Get(1, 3), peTMatrix.Get(2, 3), 1
		);

		Sphere->SetTransformMatrix(glmTMatrix);

	}

	void DemoPenduleNewton::GameEnd()
	{
		delete &AnchorPoint;
		delete &Sphere;
	}


	//void DemoPenduleNewton::LoadLevel()
	//{
	//	SetupCameraParameters();

	//	pephy::CPeRigidBody* bar = SpawnStaticBox(0,5,0);

	//	int count = 3;

	//	for (int i = -2; i < count; i++)
	//	{
	//		pephy::CPeRigidBody* ball = SpawnSphere(i, 1.75, 0);

	//		pephy::CPeForceAnchoredSpring* spring = forceSystem->CreateForceAnchoredSpring(pemaths::CPeVector3(i, 13, 0), 100, 10, pemaths::CPeVector3(0, 0.5, 0));

	//		forceSystem->AddForceToParticle(spring, ball);
	//		
	//		if (i == count - 1)
	//		{
	//			pephy::CPeForceCustomLocal* force = forceSystem->CreateForceCustomLocal(pemaths::CPeVector3(70, 0, 0), pemaths::CPeVector3());
	//			forceSystem->AddForceToParticle(force, ball, 1);
	//		}
	//	}

	//	//DemoBoxes();
	//	//DemoSpheres();
	//}

	//void DemoPenduleNewton::SpawnBox(double p_x, double p_y, double p_z)
	//{
	//	pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

	//	entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

	//	entity->m_transform.SetSize(pemaths::CPeVector3(1, 1, 1));

	//	//pemaths::CPeQuaternion rot = pemaths::CPeQuaternion(pemaths::CPeVector3(1, 0, 0), 0.785398163397448309616);
	//	//entity3->m_transform.SetOrientation(rot);

	//	pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 1e-12);

	//	rigidbodyComp->SetCubeInertia(1, 1, 1);

	//	meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");

	//	pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

	//	col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, pemaths::CPeVector3(1, 1, 1)));
	//}

	//pephy::CPeRigidBody* DemoPenduleNewton::SpawnSphere(double p_x, double p_y, double p_z)
	//{
	//	pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

	//	entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

	//	entity->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

	//	pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 1e-1);

	//	meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

	//	pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

	//	col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, 0.5, 0.999));

	//	return rigidbodyComp;
	//}

	//pephy::CPeRigidBody* DemoPenduleNewton::SpawnStaticBox(double p_x, double p_y, double p_z)
	//{
	//	pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

	//	entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

	//	entity->m_transform.SetSize(pemaths::CPeVector3(10, 1, 1));

	//	pephy::CPeRigidBody* rigidbodyComp = forceSystem->CreateRigidBodyComponent(entity, 0, 0.999, pemaths::CPeVector3(0, 0, 0));

	//	meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/companion_cube_simple.obj", "textures/viking_room.png");

	//	pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, 5);

	//	col->AddPrimitive(colliderSystem->CreateBoxShape(*entity, pemaths::CPeVector3(10, 1, 1)));

	//	return rigidbodyComp;
	//}

	//void DemoPenduleNewton::SpawnFloor()
	//{
	//	pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

	//	entity->m_transform.SetPosition(pemaths::CPeVector3(0, 0, 0));

	//	entity->m_transform.SetSize(pemaths::CPeVector3(100, 1, 100));

	//	meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/plane.obj", "textures/debug_texture.png");

	//	pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, 100);

	//	col->AddPrimitive(colliderSystem->CreatePlaneShape(*entity, pemaths::CPeVector3(0, 1, 0), 0));
	//}

	//void DemoPenduleNewton::SpawnStaticSphere(double p_x, double p_y, double p_z)
	//{
	//	pecore::CPeEntity* entity = &engine::CPeGameManager::getInstance().CreateEntity();

	//	entity->m_transform.SetPosition(pemaths::CPeVector3(p_x, p_y, p_z));

	//	entity->m_transform.SetSize(pemaths::CPeVector3(0.5, 0.5, 0.5));

	//	meshRenderSystem->CreateMeshComponent(entity, *m_renderer, "models/sphere.obj", "textures/viking_room.png");

	//	pephy::CPeColliderComponent* col = colliderSystem->CreateColliderComponent(*entity, sqrt(3));

	//	col->AddPrimitive(colliderSystem->CreateSphereShape(*entity, 0.5));
	//}

	//void DemoPenduleNewton::DemoSpheres()
	//{
	//	SpawnFloor();

	//	for (int i = -2; i < 1; i++)
	//	{
	//		for (int j = -2; j < 1; j++)
	//		{
	//			SpawnSphere(2 * i + 2, 6, 2 * j + 2);
	//		}
	//	}

	//	for (int i = 0; i < 5; i++)
	//	{
	//		SpawnSphere((i % 2) * 0.5, 6 + 2 * i, ((i + 1) % 2) * 0.5);
	//	}
	//}

	//void DemoPenduleNewton::DemoBoxes()
	//{
	//	SpawnFloor();

	//	for (int i = -2; i < 1; i++)
	//	{
	//		for (int j = -2; j < 1; j++)
	//		{
	//			SpawnBox(2 * i + 2, 6, 2 * j + 2);
	//		}
	//	}

	//	for (int i = 0; i < 5; i++)
	//	{
	//		SpawnBox((i % 2) * 0.5, 6 + 2 * i, ((i + 1) % 2) * 0.5);
	//	}
	//}

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