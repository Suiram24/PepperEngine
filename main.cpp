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
#include "CPeGameManager.h"

// Main code
int main(int, char**)
{

    engine::CPeGameMode* myGameMode = &pedemo::DemoPenduleNewton();


    engine::CPeGameManager::getInstance().SetGameMode(myGameMode);
    engine::CPeGameManager::getInstance().StartGame();

    return 0;
}
