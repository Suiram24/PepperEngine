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
		//
		// Render setup
		if (m_ActiveGameMode == nullptr)
		{
			printf("Error: game cannot start: GameMode no set");
			return;
		}

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

		//
		// Give the window and renderer to the gamemode
		m_ActiveGameMode->InitGameMode(m_window, &m_renderer);

		


		m_ActiveGameMode->GameStart();

		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
			controls::CameraController::getKeyboardInputs(m_window);

			m_renderer.beginDrawFrame();


			m_ActiveGameMode->GameUpdate();

			PhysicUpdate(ImGui::GetIO().DeltaTime);

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
		std::vector<engine::physics::CPeParticle*> particles;
		pecore::CPeEntity* entity = m_entityPool->First();
		for (size_t i = 0; i < m_entityPool->Size(); i++)
		{
			if (entity->IsActive())
			{
				if (entity->GetComponent<engine::physics::CPeColliderComponent>() != nullptr)
				{
					engine::physics::CPeParticle* part = entity->GetComponent<engine::physics::CPeParticle>();
					if (part != nullptr)
					{
						particles.push_back(part);
					}
				}
			}
			

			entity++;
		}

		engine::physics::CPeCollisionSystem::GetInstance().UpdateCollision(p_timeStep, &particles);


	}

	void CPeGameManager::AllocateObjectsPool()
	{
		m_entityPool = new pecore::CPeObjectPool<pecore::CPeEntity, pecore::consts::maxEntityNumber>();
		m_forceSystem->AllocateObjectsPool();
	}

	void CPeGameManager::FreeObjectsPool()
	{
		delete m_entityPool;
		m_forceSystem->FreeObjectsPool();
	}

	pecore::CPeEntity& CPeGameManager::CreateEntity(const pemaths::CPeTransform& p_transform)
	{
		return m_entityPool->Create(p_transform);
	}
	
}

