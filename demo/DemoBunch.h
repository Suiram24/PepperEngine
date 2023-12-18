#ifndef DEMO_DEMOBUNCH_H
#define DEMO_DEMOBUNCH_H

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
		* @brief A class for basic components regarding the physics of a 3D elements.
	*/
	class DemoBunch : public engine::CPeGameMode
	{
	public:
		DemoBunch()
			: engine::CPeGameMode()
			, entities()
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
		void SetupCameraParameters();
	private:
		void LoadLevel();
		void DrawImGuiInterface();

		pecore::CPeEntity* SpawnBox(double p_x, double p_y, double p_z);
		pecore::CPeEntity* SpawnSphere(double p_x, double p_y, double p_z);
		pecore::CPeEntity* SpawnStaticSphere(double p_x, double p_y, double p_z);
		pecore::CPeEntity* SpawnStaticBox(double p_x, double p_y, double p_z);
		pecore::CPeEntity* SpawnFloor();

	public:
	protected:
	private:
		pephy::CPeForceSystem* forceSystem;
		pephy::CPeCollisionSystem* colliderSystem;
		engine::render::CPeMeshRenderSystem* meshRenderSystem;

		std::vector<pecore::CPeEntity*> entities;
	};

}

#endif /* DEMO_DEMOBUNCH_H */