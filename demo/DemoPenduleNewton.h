#ifndef DEMO_PENDULENEWTON_H
#define DEMO_PENDULENEWTON_H

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
	class DemoPenduleNewton : public engine::CPeGameMode
	{
	public:
		DemoPenduleNewton()
			: engine::CPeGameMode()
			, world()
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

		void SpawnBox(double p_x, double p_y, double p_z);
		pephy::CPeRigidBody* SpawnSphere(double p_x, double p_y, double p_z);
		void SpawnStaticSphere(double p_x, double p_y, double p_z);
		pephy::CPeRigidBody* SpawnStaticBox(double p_x, double p_y, double p_z);
		void SpawnFloor();
		void DemoSpheres();
		void DemoBoxes();

	public:
	protected:
	private:
		pephy::CPeForceSystem* forceSystem;
		pephy::CPeCollisionSystem* colliderSystem;
		engine::render::CPeMeshRenderSystem* meshRenderSystem;

		flecs::world world;
		flecs::query<const Position, const Rotation, const RigidBody> particleQuery;

		vk::ModelWatcher* AnchorPoint;
		vk::ModelWatcher* Sphere;
	};

}

#endif /* DEMO_PENDULENEWTON_H */