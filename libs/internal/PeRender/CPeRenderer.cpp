#include "CPeRenderer.h"

#include <math.h>

namespace engine {
	namespace render {
		void CPeImGuiRenderer::SetupInterface() {
            clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); //for background color (used in RenderFrame())
            startSim = false;
            force = 0.0f;
            angle = 0;
		}

		void CPeImGuiRenderer::RenderInterface() {
            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {


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


                //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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
		}
	}
}