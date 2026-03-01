///////////////////////////////////////////////////////////////////////
// 
//  File: PepperEngine/main.cpp
//  Lib: PepperEngine
//  Brief:    
//  Author: Marius Bozane
//  Creation date: 13/09/2023
//
///////////////////////////////////////////////////////////////////////


//#include "demo/DemoBroadPhase.h"
#include "demo/DemoPenduleNewton.h"
#include "demo/DemoBillard.h"
#include "games/MaskedRobots/MaskedRobots.h"
#include "CPeGameManager.h"

// Main code
int main(int, char**)
{

    masked_robots::MaskedRobots myGameMode = masked_robots::MaskedRobots();

    engine::CPeGameManager::getInstance().SetGameMode(&myGameMode);
    engine::CPeGameManager::getInstance().StartGame();

    return 0;
}
