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
#include "libs/internal/PeMaths/PeMaths.h"
#include "libs/internal/PePhysics/PePhysics.h"

#include <math.h>
#define PI 3.141592654

#include <cstdio>

namespace maths = engine::maths;
namespace pephysics = engine::physics;


// Main code
int main(int, char**)
{
    static int angle(30);
    static float force(14);

    printf("___Physics_Test___\n");
    pephysics::CPeParticle maParticule(pephysics::CPeTransform(), 1.0);
    maParticule.SetVelocity(maths::CPeVector3(10.,10.,0));
    maParticule.GetTransform().GetPosition().PrintCoordinate();
    pemaths::CPeVector3 zero(0, 0, 0);
    

    static ImVec2 values[250] = {};
    
    

    engine::render::CPeRenderer::getInstance().RenderSetup();

    ImVec2 curPos(0, 720);
    

   


    // Main loop
    while (!glfwWindowShouldClose(engine::render::CPeRenderer::getInstance().m_window))
    {
        engine::render::CPeRenderer::getInstance().BeginFrame();
        maParticule.SetPosition(zero);
        maParticule.SetVelocity(zero);

        ImVec4 &clear_color = engine::render::CPeRenderer::getInstance().m_clear_color; //for background color (used in RenderFrame())
        ImGuiIO& io = *engine::render::CPeRenderer::getInstance().m_io; //to retrieve framerate
        static bool throwBall = false;
        static bool ballThrowed = false;
        static int sucess = 0;
        static int cnt = 0;

        auto painter = ImGui::GetBackgroundDrawList();

        painter->AddLine(ImVec2(1280, 100), ImVec2(1280, 200), ImGui::GetColorU32(ImVec4(.9, .4, .1, 1)), 30);


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            //static float force = 0.0f;
            
           
            ImGui::SetNextWindowPos(ImVec2(0,0));
            ImGui::SetNextWindowSize(ImVec2(500,200));
            ImGui::Begin("PepperEngine options");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Welcome in the pepper engine");               // Display some text (you can use a format strings too)


            ImGui::SliderInt("Angle", &angle, 0, 90);
            ImGui::SliderFloat("float", &force, 0.0f, 20.0f);
            //ImGui::ColorEdit3("Background color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Throw"))
            {
                ++cnt;
                throwBall = true;
                ballThrowed = true;
            }
            
            ImGui::Text("Number of throws : %i", cnt);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            if (sucess > 0)
            {
                ImGui::Text("Well played ! You won in %i tries", sucess);
            }
            

            ImGui::End();
        }

        if (ballThrowed == true)
        {
            if (throwBall == true)
            {
                throwBall = false;
                double radAngle = (angle * PI) / 180;
                maParticule.SetVelocity(maths::CPeVector3(force * cos(radAngle), force * sin(radAngle), 0));

                for (int i = 0; i < 250; i++)
                {

                    values[i] = curPos;
                    maParticule.Update(0.01);
                    maParticule.GetTransform().GetPosition().PrintCoordinate();
                    curPos = ImVec2(maParticule.GetTransform().GetPosition().GetX() * 100, 720 - maParticule.GetTransform().GetPosition().GetY() * 100);
                }
                
            }
            
            
            for (int i = 0; i < 249; i++)
            {
                if (values[i++].y <= 0)
                {
                    
                    break;
                }
                painter->AddLine(values[i], values[i++], ImGui::GetColorU32(ImVec4(1, 1, 1, 1)));
                if (values[i++].x >= 1280)
                {
                    if (sucess == 0 && values[i++].y >= 100 && values[i++].y <= 200)
                    {
                        sucess = cnt;
                    }
                    break;
                }
                
            }
        }
        

        //if (startSim)
        //{
        //    //
        //    // ImGUI demo code (replace with real trajectory once particle physics is implemented)
        //    struct Funcs
        //    {
        //        static float Sin(void*, int i) { return sinf(i * 0.1f); }
        //    };
        //    
        //    ImGui::Begin("Ball throw simulation");

        //    static int display_count = 70;

        //    float (*func)(void*, int) = Funcs::Sin;
        //    ImGui::PlotLines("trajectory", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
        //    ImGui::End();
        //}



        
 


        // Rendering
        engine::render::CPeRenderer::getInstance().RenderFrame();
    }

    engine::render::CPeRenderer::getInstance().RenderCleanup();
    

    return 0;
}
