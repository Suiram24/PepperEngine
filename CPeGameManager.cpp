#include "CPeGameManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"

namespace engine {

	void CPeGameManager::SetGameMode(CPeGameMode* p_gameMode)
	{
		m_ActiveGameMode = p_gameMode;
	}

	void CPeGameManager::StartGame()
	{
		
		if (m_ActiveGameMode == nullptr)
		{
			printf("Error: game cannot start: GameMode no set");
			return;
		}


		//
		// Render setup
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_window = glfwCreateWindow(vk::WIDTH, vk::HEIGHT, "Vulkan", nullptr, nullptr);

		vk::ViewManager view(m_renderer);

		// Setup controls
		controls::CameraController& hexmap = controls::CameraController::getInstance();
		controls::CameraController::setViewManager(view);
		glfwSetCursorPosCallback(m_window, controls::CameraController::cursorPositionCallback);
		glfwSetKeyCallback(m_window, controls::CameraController::keyCallback);

		//vk::CPeVulkanRenderer renderer;
		//engine::render::CPeImGuiRenderer& imguiRenderer = engine::render::CPeImGuiRenderer::getInstance();
		//imguiRenderer.SetupInterface();
		m_renderer.init(m_window);
		SetupCameraParameters();

		//
		// Give the window and renderer to the gamemode
		m_ActiveGameMode->InitGameMode(m_window, &m_renderer);
		controls::CameraController::InitialiseView();

		


		m_ActiveGameMode->GameStart();

		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
			controls::CameraController::getKeyboardInputs(m_window);

			m_renderer.beginDrawFrame();


			m_ActiveGameMode->GameUpdate();

			PhysicUpdate(ImGui::GetIO().DeltaTime);

			m_meshRenderSystem->Update();

			m_renderer.endDrawFrame();
		}

		m_ActiveGameMode->GameEnd();

	}

	void CPeGameManager::PhysicUpdate(double p_deltaTime)
	{
		double totalTime = m_UncomputedTimeLeft + p_deltaTime;
		while (totalTime > m_timeStep)
		{
			m_forceSystem->Update(m_timeStep);
			CollisionUpdate(m_timeStep);
			totalTime -= m_timeStep;
		}

		m_UncomputedTimeLeft = totalTime;		
	}

	void CPeGameManager::CollisionUpdate(double p_timeStep)
	{
		//
		// Todo: avoid this
		//std::vector<engine::physics::CPeParticle*> particles;
		//pecore::CPeEntity* entity = m_entityPool->First();
		//for (size_t i = 0; i < m_entityPool->Size(); i++)
		//{
		//	if (entity->IsActive())
		//	{
		//		if (entity->GetComponent<engine::physics::CPeColliderComponent>() != nullptr)
		//		{
		//			engine::physics::CPeParticle* part = entity->GetComponent<engine::physics::CPeParticle>();
		//			if (part != nullptr)
		//			{
		//				particles.push_back(part);
		//			}
		//		}
		//	}
		//	

		//	entity++;
		//}

		engine::physics::CPeCollisionSystem::GetInstance().UpdateCollision(p_timeStep);


	}

	void CPeGameManager::AllocateObjectsPool()
	{
		m_entityPool = new pecore::CPeObjectPool<pecore::CPeEntity, pecore::consts::maxEntityNumber>();
		m_forceSystem->AllocateObjectsPool();
		m_collisionSystem->AllocateObjectsPool();
		m_meshRenderSystem->AllocateObjectsPool();
	}

	void CPeGameManager::FreeObjectsPool()
	{
		delete m_entityPool;
		m_forceSystem->FreeObjectsPool();
		m_collisionSystem->FreeObjectsPool();
		m_meshRenderSystem->FreeObjectsPool();
	}

	pecore::CPeEntity& CPeGameManager::CreateEntity(const pemaths::CPeTransform& p_transform)
	{
		return m_entityPool->Create(p_transform);
	}

	void CPeGameManager::SetupCameraParameters()
	{
		m_renderer.SetNearPlan(0.1f);
		m_renderer.SetFarPlan(50.0f);

		controls::CameraController::ChangeCameraPosition(-5, 10, -5);
		controls::CameraController::ChangeCameraOrientation(0, 0, 0);

		controls::CameraController::ChangeDisplacementSensitivity(0.1f);
		controls::CameraController::ChangeOrientationSensitivity(0.005f);

		controls::CameraController::InitialiseView();
	}
	
}

