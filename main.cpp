///////////////////////////////////////////////////////////////////////
// 
//  File: PepperEngine/main.cpp
//  Lib: PepperEngine
//  Brief:    
//  Author: Marius Bozane
//  Creation date: 13/09/2023
//
///////////////////////////////////////////////////////////////////////

#include "libs/internal/PeRender/CPeVulkanRenderer.h"
#include "libs/internal/PeRender/CPeGraphicalObjects.h"
#include "libs/internal/PeRender/SphereMesh.h"

#include <stdio.h>          // printf, fprintf
#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cmath>

// Main code
int main(int, char**)
{
    //engine::render::CPeRenderer::getInstance().RenderSetup();
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(vk::WIDTH, vk::HEIGHT, "Vulkan", nullptr, nullptr);

    vk::CPeVulkanRenderer renderer;
    engine::render::CPeImGuiRenderer& imguiRenderer = engine::render::CPeImGuiRenderer::getInstance();
    imguiRenderer.SetupInterface();
    renderer.init(window, &imguiRenderer);

    //vk::ModelWatcher model1(renderer, "models/viking_room.obj");
    vk::SphereMesh model2(renderer);

    //vk::ModelWatcher model2(renderer, "models/viking_room.obj");

    float i = 0.f;
    model2.SetScale(0.5f);
    model2.SetPos(0, -1, -1);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        //model1.SetPos(0, 0, std::sin(i));
        //model2.SetPos(std::sin(i), 0, 0);
        //model2.SetScale(std::abs(std::sin(i)) * 2);
        glfwPollEvents();
        renderer.drawFrame();
        i += 0.1f;
    }
    

    return 0;
}
