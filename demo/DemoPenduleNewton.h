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

	struct vector {
		PECOMPONENT("Vector",1)
		//static constexpr int compTypeID = 1;					
		//static int CompId()												
		//{															
		//	return 1;										
		//}

		float x;
		float y;

		void PrintString()
		{
			printf("Vector : %f,%f \n", x, y);
		}
	};

	struct hp {
		PECOMPONENT("HP",2)
		float currentHP = 100;
		float maxHP = 100;

		void PrintString()
		{
			printf("HP : %.1f/%.1f \n", currentHP, maxHP);
		}
	};

	struct ally {
		PECOMPONENT("Ally",3)
	};

	struct ennemy {
		PECOMPONENT("Ennemy",4)
	};


	/**
		* @brief A class for basic components regarding the physics of a 3D elements.
	*/
	class DemoPenduleNewton : public engine::CPeGameMode
	{
	public:
		DemoPenduleNewton()
			: engine::CPeGameMode()
			, entity1(nullptr)
			, entity2(nullptr)
			, entity3(nullptr)
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

		pecore::CPeEntity* entity1;
		pecore::CPeEntity* entity2;
		pecore::CPeEntity* entity3;


	};

}

#endif /* DEMO_PENDULENEWTON_H */