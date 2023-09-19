///////////////////////////////////////////////////////////////////////
// 
//  File: PepperEngine/main.cpp
//  Lib: PepperEngine
//  Brief:    
//  Author: Marius Bozane
//  Creation date: 13/09/2023
//
///////////////////////////////////////////////////////////////////////

#include "libs/internal/PERender/CPeRenderer.h"

#include <math.h>

// Main code
int main(int, char**)
{
    engine::render::CPeRenderer::getInstance().RenderSetup();

    // Main loop
    while (!glfwWindowShouldClose(engine::render::CPeRenderer::getInstance().m_window))
    {
        engine::render::CPeRenderer::getInstance().BeginFrame();
        

        ImVec4 &clear_color = engine::render::CPeRenderer::getInstance().m_clear_color; //for background color (used in RenderFrame())
        ImGuiIO& io = *engine::render::CPeRenderer::getInstance().m_io; //to retrieve framerate
        static bool startSim = false;

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float force = 0.0f;
            static int angle = 0;
           

            ImGui::Begin("PepperEngine options");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Welcome in the pepper engine");               // Display some text (you can use a format strings too)


            ImGui::SliderInt("Angle", &angle, 0, 90);
            ImGui::SliderFloat("float", &force, 0.0f, 100.0f);
            ImGui::ColorEdit3("Background color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Start simulation"))
            {
                startSim = true;
                ImGui::SetNextWindowPos(ImVec2(300, 300));
                ImGui::SetNextWindowSize(ImVec2(800, 120));
            }
            

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        if (startSim)
        {
            //
            // ImGUI demo code (replace with real trajectory once particle physics is implemented)
            struct Funcs
            {
                static float Sin(void*, int i) { return sinf(i * 0.1f); }
            };
            
            ImGui::Begin("Ball throw simulation");

            static int display_count = 70;

            float (*func)(void*, int) = Funcs::Sin;
            ImGui::PlotLines("trajectory", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
            ImGui::End();
        }


        // Rendering
        engine::render::CPeRenderer::getInstance().RenderFrame();
    }

    engine::render::CPeRenderer::getInstance().RenderCleanup();
    

    return 0;
}
