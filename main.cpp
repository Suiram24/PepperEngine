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
    pephysics::CPeParticle particuleTest(pephysics::CPeTransform(), 1.0);
    particuleTest.SetGravity(maths::CPeVector3(0., 0., 0.));
    pephysics::CPeForces* uneForce = new pephysics::CPeForces(1., 1., 0.);

    particuleTest.AddForce(uneForce);

    delete uneForce;

    //
    // Game initialization
    static int angle(30);
    static float force(14);
    printf("___Physics_Test___\n");
    pephysics::CPeParticle maParticule(pephysics::CPeTransform(), 1.0);
    maParticule.SetVelocity(maths::CPeVector3(10.,10.,0));
    maParticule.GetTransform().GetPosition().PrintCoordinate();
    pemaths::CPeVector3 zero(0, 0, 0);
    static ImVec2 values[250] = {};
    ImVec2 curPos(0, 720);
    static bool throwBall = false;
    static bool ballThrowed = false;
    static int sucess = 0;
    static int cnt = 0;
    
    //
    //Setup render (Imgui + vulkan + GLFW)
    engine::render::CPeRenderer::getInstance().RenderSetup();



    //
    // Main loop
    while (!glfwWindowShouldClose(engine::render::CPeRenderer::getInstance().m_window))
    {
        engine::render::CPeRenderer::getInstance().BeginFrame();

        //
        // reset particle (we compute the entire movement every frame for this exemple)
        maParticule.SetPosition(zero);
        maParticule.SetVelocity(zero);

        //
        // retrieve Imgui objects
        ImVec4 &clear_color = engine::render::CPeRenderer::getInstance().m_clear_color; //for background color (used in RenderFrame())
        ImGuiIO& io = *engine::render::CPeRenderer::getInstance().m_io; //to retrieve framerate
        auto painter = ImGui::GetBackgroundDrawList();

        //
        // Draw the target
        painter->AddLine(ImVec2(1280, 100), ImVec2(1280, 200), ImGui::GetColorU32(ImVec4(.9, .4, .1, 1)), 30);

        //
        // Draw the GUI
        {
            ImGui::SetNextWindowPos(ImVec2(0,0));
            ImGui::SetNextWindowSize(ImVec2(500,200));
            ImGui::Begin("PepperEngine options");       
            ImGui::Text("Welcome in the pepper engine");
            ImGui::SliderInt("Angle", &angle, 0, 90);
            ImGui::SliderFloat("float", &force, 0.0f, 20.0f);

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


        //
        // Game logic
        if (ballThrowed == true) //draw only after ball is throwed once
        {
            if (throwBall == true) //Only called once per throw button press
            {
                //
                // Compute the entire movement of the ball
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
            
            //
            // Draw (every frame) the movement with a dotted line
            for (int i = 0; i < 249; i++)
            {
                if (values[i++].y <= 0)
                {
                    break;
                }

                painter->AddLine(values[i], values[i++], ImGui::GetColorU32(ImVec4(1, 1, 1, 1)));

                if (values[i++].x >= 1280)
                {
                    //
                    // Sucess condition
                    if (sucess == 0 && values[i++].y >= 100 && values[i++].y <= 200)
                    {
                        sucess = cnt;
                    }
                    break;
                }
                
            }
        }
        

        // Rendering
        engine::render::CPeRenderer::getInstance().RenderFrame();
    }

    engine::render::CPeRenderer::getInstance().RenderCleanup();
    

    return 0;
}
