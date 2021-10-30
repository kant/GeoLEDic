#include "MidiMenu.hpp"
#include "ImGui.hpp"

MidiMenu::MidiMenu(MidiSource& midi_source, ProgramFactory& program_factory):
   m_midi_source(midi_source),
   m_factory(program_factory)
{
}

void MidiMenu::drawMenu()
{
   m_factory.drawMenu(m_midi_source.getSender(), &m_piano);

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
   if (m_midi_source.getMidiControllers() and ImGui::TreeNode("Controllers"))
   {
      showMidiPorts(*m_midi_source.getMidiControllers(), m_midi_controllers);
      ImGui::TreePop();
   }

   if (m_midi_source.getSender())
   {
      MidiSource::MidiSender& sender(*m_midi_source.getSender());
      if (sender.enabled() && ImGui::Button("Pause MIDI Output"))
      {
         sender.enable(false);
      }
      else if (not sender.enabled() && ImGui::Button("Resume MIDI Output"))
      {
         sender.enable(true);
         m_factory.program().sendSnapshot(m_midi_source.getSender());
      }
      ImGui::SameLine(); HelpMarker("Pause the MIDI output to play with controls and change programs without sending "
                                    "to the output port. When you resume, a snapshot of the current program number "
                                    "and controller values is sent immediately");

      if (sender.enabled())
      {
         if (ImGui::Button("Send Snapshot"))
         {
            m_factory.program().sendSnapshot(m_midi_source.getSender());
         }
         ImGui::SameLine(); HelpMarker("Send the current program number and all controller values");
      }
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

void MidiMenu::noteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
   m_piano.noteOn(note, velocity, channel);
}

void MidiMenu::noteOff(uint8_t note, uint8_t channel)
{
   m_piano.noteOff(note, channel);
}