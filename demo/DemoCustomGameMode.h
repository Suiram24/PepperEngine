#ifndef DEMO_DEMOCUSTOMGAMEMODE_H
#define DEMO_DEMOCUSTOMGAMEMODE_H

#include "..\CPeGameMode.h"
#include "..\CPeGameManager.h"
#include "..\libs\internal\PeRender\SphereMesh.h"
#include "..\Libs\internal\PeEngineCore\PeEngineCore.h"
#include "..\Libs\internal\PePhysics\PePhysics.h"

#include <optional>

namespace pedemo {
	namespace pephy = engine::physics;
	
	/**
		* @brief A class for basic components regarding the physics of a 3D elements.
	*/
	class DemoCustomGameMode: public engine::CPeGameMode
	{
	public:
		DemoCustomGameMode()
			: engine::CPeGameMode()
			, entity1(nullptr)
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



	public:
	protected:
	private:
		pephy::CPeForceSystem* forceSystem;
		//std::optional<vk::SphereMesh> sphere1;
		//std::optional<vk::SphereMesh> sphere2;
		int i;

		pecore::CPeEntity* entity1;

	};
	
}

#endif /* DEMO_DEMOCUSTOMGAMEMODE_H */