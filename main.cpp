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

#include <stdio.h>          // printf, fprintf
#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

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

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        renderer.drawFrame();
    }
    

    return 0;
}
