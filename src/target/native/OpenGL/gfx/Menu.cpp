#include "Menu.hpp"
#ifdef WITH_GLEW
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

extern void drawProgram();

namespace gfx {

Menu::Menu(Config& config, GLFWwindow* window):
   m_config(config),
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
   ImGui::SetNextWindowBgAlpha(0.2f);

   ImGui::Begin("Settings");
   
   if (m_config.topMenuPresenter())
   {
      m_config.topMenuPresenter()->drawMenu();
   }
   
   ImGui::Separator();
   
   if (m_config.midiPorts() and ImGui::TreeNode("MIDI Source"))
   {
      showMidiPorts(*m_config.midiPorts(), m_midi_sources);
      ImGui::TreePop();
   }
   if (m_config.midiOutPorts() and ImGui::TreeNode("MIDI Destination"))
   {
      showMidiPorts(*m_config.midiOutPorts(), m_midi_destinations);
      ImGui::TreePop();
   }
   
   ImGui::Separator();
   
   if (ImGui::TreeNode("Shader"))
   {
      ImGui::SliderFloat("Cutoff Distance", &m_config.m_cutoff_distance, 0.0f, 10.0f);
      ImGui::Text("Attenuation:");
      ImGui::SliderFloat("Constant", &m_config.m_attenuation_constant, 0.0f, 10.0f);
      ImGui::SliderFloat("Linear", &m_config.m_attenuation_linear, 0.0f, 300.0f);
      ImGui::SliderFloat("Square", &m_config.m_attenuation_square, 0.0f, 1000.0f);
      ImGui::TreePop();
   }
   ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
   ImGui::End();
      
   ImGui::Render();
   int display_w, display_h;
   glfwGetFramebufferSize(m_window, &display_w, &display_h);
   glViewport(0, 0, display_w, display_h);
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
   
void Menu::showMidiPorts(Config::MidiPorts& ports, MidiPortMap& port_map)
{
   Config::MidiPorts::PortId initial_selected_port, selected_port = 0;
   ports.updateAvailablePorts(port_map, selected_port);
   initial_selected_port = selected_port;
   
   ImGui::Bullet();
   if (ImGui::Selectable("None", selected_port == 0))
   {
      selected_port = 0;
   }
   
   for (auto& port: port_map)
   {
      ImGui::Bullet();
      if (ImGui::Selectable(port.second.c_str(), selected_port == port.first))
      {
         selected_port = port.first;
      }
   }
   
   if (selected_port != initial_selected_port)
   {
      ports.selectPort(selected_port);
   }
}




}
