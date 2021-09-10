#include "MidiMenu.hpp"
#include "imgui/imgui.h"

MidiMenu::MidiMenu(MidiSource& midi_source, ProgramFactory& program_factory):
   m_midi_source(midi_source),
   m_factory(program_factory)
{
}

void MidiMenu::drawMenu()
{
   m_factory.drawMenu();

   ImGui::Separator();
   
   if (m_midi_source.getMidiInPorts() and ImGui::TreeNode("MIDI Source"))
   {
      showMidiPorts(*m_midi_source.getMidiInPorts(), m_midi_sources);
      ImGui::TreePop();
   }
   if (m_midi_source.getMidiOutPorts() and ImGui::TreeNode("MIDI Destination"))
   {
      showMidiPorts(*m_midi_source.getMidiOutPorts(), m_midi_destinations);
      ImGui::TreePop();
   }
}

void MidiMenu::showMidiPorts(MidiSource::MidiPorts& ports, MidiPortMap& port_map)
{
   MidiSource::MidiPorts::PortId initial_selected_port, selected_port = 0;
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
