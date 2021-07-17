#include "Menu.hpp"
#ifdef WITH_GLEW
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace gfx {

Menu::Menu(const Config& /*config*/, GLFWwindow* window):
   m_window(window)
{
   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();

   // Setup Dear ImGui style
   ImGui::StyleColorsDark();
   ImGui_ImplGlfw_InitForOpenGL(m_window, true);
   ImGui_ImplOpenGL3_Init("#version 150");
}

Menu::~Menu()
{
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
}
   
void Menu::draw()
{
   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();
   
   ImGui::Begin("Settings");
   ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
   ImGui::End();
   
   ImGui::Render();
   int display_w, display_h;
   glfwGetFramebufferSize(m_window, &display_w, &display_h);
   glViewport(0, 0, display_w, display_h);
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
   
}
