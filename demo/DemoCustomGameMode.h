#ifndef DEMO_DEMOCUSTOMGAMEMODE_H
#define DEMO_DEMOCUSTOMGAMEMODE_H

#include "..\CPeGameMode.h"
#include "..\libs\internal\PeRender\SphereMesh.h"

#include <optional>

namespace pedemo {
	
	/**
		* @brief A class for basic components regarding the physics of a 3D elements.
	*/
	class DemoCustomGameMode: public engine::CPeGameMode
	{
	public:
		DemoCustomGameMode()
			: engine::CPeGameMode()
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

		//std::optional<vk::SphereMesh> sphere1;
		//std::optional<vk::SphereMesh> sphere2;
		int i;

	};
	
}

#endif /* DEMO_DEMOCUSTOMGAMEMODE_H */