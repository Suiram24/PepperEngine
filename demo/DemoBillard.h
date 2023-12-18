#ifndef DEMO_BILLARD_H
#define DEMO_BILLARD_H

#include "..\CPeGameMode.h"
#include "..\CPeGameManager.h"
#include "..\libs\internal\PeRender\PeRender.h"
#include "..\Libs\internal\PeEngineCore\PeEngineCore.h"
#include "..\Libs\internal\PePhysics\PePhysics.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"

namespace pedemo {
	namespace pephy = engine::physics;

	/**
		* @brief A billard demonstration
	*/
	class DemoBillard : public engine::CPeGameMode
	{
	public:
		DemoBillard()
			: engine::CPeGameMode()
			, whiteBall(nullptr)
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
		void DrawImGuiInterface();

		pecore::CPeEntity* SpawnSphere(const pemaths::CPeVector3& p_pos, const pemaths::CPeVector3& p_size);
		void SpawnStaticBox(const pemaths::CPeVector3& p_pos, const pemaths::CPeVector3& p_size);
		void SpawnFloor();

	public:
	protected:
	private:
		pephy::CPeForceSystem* forceSystem;
		pephy::CPeCollisionSystem* colliderSystem;
		engine::render::CPeMeshRenderSystem* meshRenderSystem;

		pecore::CPeEntity* whiteBall;


	};

}

#endif /* DEMO_BILLARD_H */