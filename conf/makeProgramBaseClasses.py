import sys
import programs
from string import Template

def getProgram(classname):
    for prog in programs.get():
        if prog['program'] == classname:
            return prog
    raise Exception("Could not find program named %s" % classname)

def getPrototypes(program, classname):
    prototypes = []
    for cc in program['controls']:
        name = cc['name'].title().replace(' ','')
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
    for cc in program['controls']:
        getter = "getControlValue(%d)" % cc['number']
        impl = cc['prototype'] + "\n{\n"
        if cc['type'] == 'toggle':
            impl = impl + "    return %s > 63;\n}" % getter
        elif cc['type'] == 'enum':
            impl = impl + "    uint8_t v = %s;\n   " % getter
            for i in range(len(cc['enums']) - 1, 0, -1):
                impl = impl + " if (v >= %d)\n    {\n" % cc['values'][i]
                impl = impl + "        return %s_%s;\n    }\n    else" % (cc['enum_type'], cc['enums'][i])
            impl = impl + "\n    {\n"
            impl = impl + "        return %s_%s;\n    }\n}" % (cc['enum_type'], cc['enums'][0])
        else:
            impl = impl + "    return %s;\n}" % getter
        implementations.append(impl)
    return implementations

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

namespace generated {

$implementations

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
    virtual ~$classname(){}

    $enums

    $prototypes
};

}
#endif
'''

program = getProgram(classname)
prototypes = getPrototypes(program, classname)
enums = getEnums(program)
impls = getImplementations(program)
base = program['base'] if 'base' in program else 'Controls'

with open(basename, 'w') as file:
    file.write(Template(CPP_TEMPLATE).substitute(
        classname=classname,
        implementations="\n".join(impls)))

with open(header, 'w') as file:
    file.write(Template(HPP_TEMPLATE).substitute(
        classname=classname,
        base=base,
        prototypes="\n    ".join(prototypes),
        enums="\n    ".join(enums)))
