///////////////////////////////////////////////////////////////////////
// 
//  File: PepperEngine/main.cpp
//  Lib: PepperEngine
//  Brief:    
//  Author: Marius Bozane
//  Creation date: 13/09/2023
//
///////////////////////////////////////////////////////////////////////


//#include "demo/DemoCustomGameMode.h"
#include "demo/DemoPhase3.h"
#include "demo/DemoDoublePendulum.h"
#include "CPeGameManager.h"

// Main code
int main(int, char**)
{

    //engine::CPeGameMode* myGameMode = &pedemo::DemoPhase3();
    engine::CPeGameMode* myGameMode = &pedemo::DemoDoublePendulum();


    engine::CPeGameManager::getInstance().SetGameMode(myGameMode);
    engine::CPeGameManager::getInstance().StartGame();

    return 0;
}
