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
#include "libs/internal/PeMaths/PeMaths.h"
#include "libs/internal/PePhysics/PePhysics.h"

#include <cstdio>        // printf, fprintf
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cmath>

namespace maths = engine::maths;
namespace pephysics = engine::physics;

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
    renderer.init(window);

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
        renderer.beginDrawFrame();
        imguiRenderer.RenderInterface();
        renderer.endDrawFrame();
        i += 0.1f;
      /*
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
          */
    }
    return 0;
}
