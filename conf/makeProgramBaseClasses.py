import sys
import programs
from string import Template

def getProgram(classname):
    program_number = 0
    for prog in programs.get():
        if prog['program'] == classname:
            return prog, program_number
        program_number = program_number + 1
    raise Exception("Could not find program named %s" % classname)

def getPrototypes(program, classname):
    prototypes = []
    for cc in program['controls']:
        name = ''.join(e for e in cc['name'].title() if e.isalnum())
        if cc['type'] == 'toggle':
            cc['prototype'] = "bool %s::is%s() const" % (classname, name)
            prototypes.append("bool is%s() const;" % name)
        elif cc['type'] == 'enum':
            cc['enum_type'] = name
            cc['prototype'] = "%s::%s %s::get%s() const" % (classname, name, classname, name)
            prototypes.append("%s get%s() const;" % (name, name))
        else:
            cc['prototype'] = "uint8_t %s::get%s() const" % (classname, name)
            prototypes.append("uint8_t get%s() const;" % name)
    return prototypes

def getEnums(program):
    enums = []
    for cc in program['controls']:
        if cc['type'] != 'enum':
            continue
        enum = "enum %s\n    {\n" % cc['enum_type']
        for i in range(0, len(cc['enums'])):
            enum = enum + "        %s_%s" % (cc['enum_type'], cc['enums'][i])
            if i < len(cc['enums']) - 1:
                enum = enum + ",\n"
            else:
                enum = enum + "\n    };"
        enums.append(enum)
    return enums
        
def getImplementations(program):
    implementations = []
    snapshots = ""
    defaults = ""
    for cc in program['controls']:
        getter = "getControlValue(%d)" % cc['number']
        impl = cc['prototype'] + "\n{\n"
        if cc['type'] == 'toggle':
            impl = impl + "    return %s > 63;\n}" % getter
            if 'default' in cc and cc['default']:
                defaults = defaults + "    setControlValue(%u, %u); // default for %s\n" % (cc['number'], 127 ,cc['name'])
        elif cc['type'] == 'enum':
            impl = impl + "    uint8_t v = %s;\n   " % getter
            for i in range(len(cc['enums']) - 1, 0, -1):
                impl = impl + " if (v >= %d)\n    {\n" % cc['values'][i]
                impl = impl + "        return %s_%s;\n    }\n    else" % (cc['enum_type'], cc['enums'][i])
            impl = impl + "\n    {\n"
            impl = impl + "        return %s_%s;\n    }\n}" % (cc['enum_type'], cc['enums'][0])
        else:
            impl = impl + "    return %s;\n}" % getter
            if 'default' in cc:
                defaults = defaults + "    setControlValue(%u, %u); // default for %s\n" % (cc['number'],cc['default'],cc['name'])
        snapshots = snapshots + "    sender->sendControlChange(%u, m_control_values[%u]);\n" % (cc['number'], cc['number'])
        implementations.append(impl)
    # add constructor with defaults at beginning
    implementations.insert(0, "%s::%s()\n{\n%s}" % (program['program'], program['program'], defaults))
    return implementations, snapshots

IMGUI_SLIDER_TEMPLATE = '''
    {
        const uint8_t cmin = $min;
        const uint8_t cmax = $max;
        if (ImGui::SliderScalar("$name", ImGuiDataType_U8, &m_control_values[$cc_num], &cmin, &cmax))
        {
            if (sender) sender->sendControlChange($cc_num, m_control_values[$cc_num]);
        }
    }
'''

IMGUI_TOGGLE_TEMPLATE = '''
    {
        bool v = m_control_values[$cc_num] >= 64;
        bool prev = v;
        ImGui::Checkbox("$name", &v);
        if (v != prev)
        {
            m_control_values[$cc_num] = v ? 127 : 0;
           if (sender) sender->sendControlChange($cc_num, m_control_values[$cc_num]);
        }
    }
'''

IMGUI_ENUM_TEMPLATE = '''
    {
        const char* items[] = {
            $enums
        };
        const uint8_t values[] = { $values };
        int index = 0;
        uint8_t value = m_control_values[$cc_num];
        for (index = sizeof(values)-1; index >= 0; index--)
        {
           if (values[index] <= value)
           {
              break;
           }
        }
        
        const char* combo_preview_value = items[index];
        if (ImGui::BeginCombo("$name", combo_preview_value))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (index == n);
                if (ImGui::Selectable(items[n], is_selected))
                {
                    index = n;
                    m_control_values[$cc_num] = values[index];
                    if (sender) sender->sendControlChange($cc_num, m_control_values[$cc_num]);
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
'''

def getMenu(program):
    menu = ""
    for cc in program['controls']:
        name = cc['name']
        if cc['type'] == 'toggle':
            menu = menu + Template(IMGUI_TOGGLE_TEMPLATE).substitute(
               name=cc['name'],
               cc_num=cc['number'])
        elif cc['type'] == 'enum':
            menu = menu + Template(IMGUI_ENUM_TEMPLATE).substitute(
               name=cc['name'],
               cc_num=cc['number'],
               enums='"' + '",\n            "'.join(cc['enums']) + '"',
               values=', '.join(str(x) for x in cc['values']))
        else:
            menu = menu + Template(IMGUI_SLIDER_TEMPLATE).substitute(
               name=cc['name'],
               cc_num=cc['number'],
               min=cc['min'],
               max=cc['max'])
        help = "CC %d" % cc['number']
        if 'description' in cc:
            help = help + " - " + cc['description']
        menu = menu + '    ImGui::SameLine(); HelpMarker("%s");\n' % help
    return menu

command = sys.argv[2] if len(sys.argv) > 2 else ''
basename = sys.argv[1]

if command == '--sources':
    filenames = ''
    for p in programs.get():
        filenames = filenames + "%s/%s.generated.cpp;" % (basename, p['program'])
    # don't use print as we don't want a newline
    sys.stdout.write(filenames[:-1])
    exit(1)


header    = basename.replace('.generated.cpp','.hpp')
classname = basename.replace('.generated.cpp','').split('/')[-1]

CPP_TEMPLATE = '''
#include "${classname}.hpp"
#ifdef WITH_GFX
#include "ImGui.hpp"
#endif

namespace generated {

$implementations

#ifdef WITH_GFX
void ${classname}::drawMenu(MidiSource::MidiSender* sender)
{
    {
        const uint8_t cmin = 0;
        const uint8_t cmax = 255;
        if (ImGui::SliderScalar("Brightness", ImGuiDataType_U8, &getBrightness(), &cmin, &cmax))
        {
            if (sender) sender->sendControlChange(7, getBrightness()/2);
        }
    }
$menu
}

void ${classname}::sendSnapshot(MidiSource::MidiSender* sender)
{
    if (sender == nullptr) return;
    sender->sendProgramChange($program_number);
$control_snapshot
}

#endif

}
'''

HPP_TEMPLATE = '''
#ifndef _GENERATED_${classname}_HPP
#define _GENERATED_${classname}_HPP

#include "$base.hpp"

namespace generated {

class $classname: public $base
{
public:
    $classname();
    virtual ~$classname(){}

    $enums

    $prototypes
#ifdef WITH_GFX
    virtual void drawMenu(MidiSource::MidiSender* sender);
    virtual void sendSnapshot(MidiSource::MidiSender* sender);
#endif
};

}
#endif
'''

program, program_number = getProgram(classname)
prototypes = getPrototypes(program, classname)
enums = getEnums(program)
impls, control_snapshots = getImplementations(program)
menu  = getMenu(program)
base = program['base'] if 'base' in program else 'Controls'

with open(basename, 'w') as file:
    file.write(Template(CPP_TEMPLATE).substitute(
        classname=classname,
        menu=menu,
        implementations="\n".join(impls),
        program_number=program_number,
        control_snapshot=control_snapshots))

with open(header, 'w') as file:
    file.write(Template(HPP_TEMPLATE).substitute(
        classname=classname,
        base=base,
        prototypes="\n    ".join(prototypes),
        enums="\n    ".join(enums)))
