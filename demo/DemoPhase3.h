#ifndef DEMO_DEMOPHASE3_H
#define DEMO_DEMOPHASE3_H

#include "..\CPeGameMode.h"
#include "..\CPeGameManager.h"
#include "..\libs\internal\PeRender\PeRender.h"
#include "..\Libs\internal\PeEngineCore\PeEngineCore.h"
#include "..\Libs\internal\PePhysics\PePhysics.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"

#include <optional>

namespace pedemo {
	namespace pephy = engine::physics;

	/**
		* @brief A class for basic components regarding the physics of a 3D elements.
	*/
	class DemoPhase3 : public engine::CPeGameMode
	{
	public:
		DemoPhase3()
			: engine::CPeGameMode()
			, entity1(nullptr)
			, entity2(nullptr)
			, entity3(nullptr)
			, entity4(nullptr)
		{
		}

		/**
		 * @brief Function called once at the start of the game
		*/
		virtual void GameStart();

		/**
		 * @brief Function called once every frame. Put your game logic here.
		*/
		virtual void GameUpdate();

		/**
		 * @brief Function called once at the end of the game
		*/
		virtual void GameEnd();
	protected:
	private:
		void LoadLevel();


	public:
	protected:
	private:
		pephy::CPeForceSystem* forceSystem;
		pephy::CPeCollisionSystem* colliderSystem;
		engine::render::CPeMeshRenderSystem* meshRenderSystem;
		//std::optional<vk::SphereMesh> sphere1;
		//std::optional<vk::SphereMesh> sphere2;
		int i;

		pecore::CPeEntity* entity1;
		pecore::CPeEntity* entity2;
		pecore::CPeEntity* entity3;
		pecore::CPeEntity* entity4;

		pephy::CPeForceCustomLocal* freeEditable1;
		pephy::CPeForceCustomLocal* freeEditable2;

		pecore::CPeEntity* floorEntities[10][10];



	};

}

#endif /* DEMO_DEMOCUSTOMGAMEMODE_H */