///////////////////////////////////////////////////////////////////////
// 
//  File: PepperEngine/main.cpp
//  Lib: PepperEngine
//  Brief:    
//  Author: Marius Bozane
//  Creation date: 13/09/2023
//
///////////////////////////////////////////////////////////////////////


#include "demo/DemoBroadPhase.h"
#include "demo/DemoPenduleNewton.h"
#include "demo/DemoBillard.h"
#include "CPeGameManager.h"

// Main code
int main(int, char**)
{
    
    pedemo::DemoPenduleNewton myGameMode = pedemo::DemoPenduleNewton();
    //engine::CPeGameMode* myGameMode = &pedemo::DemoBillard();


    engine::CPeGameManager::getInstance().SetGameMode(&myGameMode);
    engine::CPeGameManager::getInstance().StartGame();



    return 0;
}
