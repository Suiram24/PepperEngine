#include "CPeRenderer.h"

namespace engine
{
    namespace render
    {
        static void glfw_error_callback(int error, const char* description)
        {
            fprintf(stderr, "GLFW Error %d: %s\n", error, description);
        }
        static void check_vk_result(VkResult err)
        {
            if (err == 0)
                return;
            fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
            if (err < 0)
                abort();
        }

#ifdef IMGUI_VULKAN_DEBUG_REPORT
        static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
        {
            (void)flags; (void)object; (void)location; (void)messageCode; (void)pUserData; (void)pLayerPrefix; // Unused arguments
            fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
            return VK_FALSE;
        }
#endif // IMGUI_VULKAN_DEBUG_REPORT



        CPeRenderer::~CPeRenderer()
        {
        }

        int CPeRenderer::RenderSetup()
        {
            glfwSetErrorCallback(glfw_error_callback);
            if (!glfwInit())
                return 1;

            // Create window with Vulkan context
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            m_window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+Vulkan example", nullptr, nullptr);
            if (!glfwVulkanSupported())
            {
                printf("GLFW: Vulkan Not Supported\n");
                return 1;
            }

            //Setup Vulkan
            vulkanRenderer.init(m_window);

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            m_io = &ImGui::GetIO(); 
            //(void)m_io;
            m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();

            // Load Fonts
            // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
            // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
            // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
            // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
            // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
            // - Read 'docs/FONTS.md' for more instructions and details.
            // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
            //io.Fonts->AddFontDefault();
            //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
            //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
            //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
            //IM_ASSERT(font != nullptr);

            /*
            // Upload Fonts
            {
                // Use any command queue
                VkCommandPool command_pool = m_wd->Frames[m_wd->FrameIndex].CommandPool;
                VkCommandBuffer command_buffer = m_wd->Frames[m_wd->FrameIndex].CommandBuffer;

                m_err = vkResetCommandPool(vk::g_Device, command_pool, 0);
                check_vk_result(m_err);
                VkCommandBufferBeginInfo begin_info = {};
                begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
                m_err = vkBeginCommandBuffer(command_buffer, &begin_info);
                check_vk_result(m_err);

                ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

                VkSubmitInfo end_info = {};
                end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                end_info.commandBufferCount = 1;
                end_info.pCommandBuffers = &command_buffer;
                m_err = vkEndCommandBuffer(command_buffer);
                check_vk_result(m_err);
                m_err = vkQueueSubmit(vk::g_Queue, 1, &end_info, VK_NULL_HANDLE);
                check_vk_result(m_err);

                m_err = vkDeviceWaitIdle(vk::g_Device);
                check_vk_result(m_err);
                ImGui_ImplVulkan_DestroyFontUploadObjects();
            }
            */

            // Our state
            m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            return EXIT_SUCCESS;
        }


        int CPeRenderer::RenderCleanup()
        {
            // Cleanup
            vulkanRenderer.cleanup();
            check_vk_result(m_err);
            ImGui_ImplVulkan_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            glfwDestroyWindow(m_window);
            glfwTerminate();

            return 0;
        }

        void CPeRenderer::BeginFrame()
        {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }


        void CPeRenderer::RenderFrame()
        {
            // Rendering
            ImGui::Render();
            vulkanRenderer.drawFrame();
            ImDrawData* draw_data = ImGui::GetDrawData();
            const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
            if (!is_minimized)
            {
                m_wd->ClearValue.color.float32[0] = m_clear_color.x * m_clear_color.w;
                m_wd->ClearValue.color.float32[1] = m_clear_color.y * m_clear_color.w;
                m_wd->ClearValue.color.float32[2] = m_clear_color.z * m_clear_color.w;
                m_wd->ClearValue.color.float32[3] = m_clear_color.w;
            }
        }

    }//namespace render
}//namespace engine
