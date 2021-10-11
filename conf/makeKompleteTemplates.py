#!/usr/bin/python

import programs
import copy

INDENT_STEP = "    "

MIDI_TYPES = {
    "control_change": 3,
    "program_change": 4
}

BEHAVIOUR = {
    "toggle": 0,
    "trigger": 1
}

COLORS = {
    "red": 1,
    "orange": 2,
    "light orange": 3,
    "warm yellow": 4,
    "yellow": 5,
    "lime": 6,
    "green": 7,
    "mint": 8,
    "turquoise": 9,
    "cyan": 10,
    "blue": 11,
    "plum": 12,
    "violet": 13,
    "purple": 14,
    "magenta": 15,
    "fuchsia": 16
}

def writeKeyZone(indent, keyzone):
    channel = (keyzone['channel'] if 'channel' in keyzone else 0)

    colorname = keyzone['color'] if 'color' in keyzone else 'red'
    color = COLORS[colorname] if colorname in COLORS else 1

    print indent, '"UpperKey": "%d",' % (keyzone['to'] if 'to' in keyzone else 127)
    print indent, '"Transpose": "%d",' % (keyzone['transpose'] if 'transpose' in keyzone else 0)
    print indent, '"Channel": "%d",' % channel
    print indent, '"Off": "%s",' % (keyzone['off'] if 'off' in keyzone else 'false')
    print indent, '"Color": "%d"' % color


def writeKeyZones(indent, keyzones):
    # copy as we modify elements
    keyzones = copy.deepcopy(keyzones)
    # disable keys in the gaps between zones
    i = 0
    last_to = 0
    while i < len(keyzones):
        if (keyzones[i]['from'] > last_to + 1):
            keyzones.insert(i, {'off': 'true', 'from': last_to + 1, 'to': keyzones[i]['from'] - 1})
        last_to = keyzones[i]['to']
        i = i+1
    # disable remaining keys if we're not using all of them

    if last_to != 127:
        keyzones.append({'off': 'true', 'to': 127})

    for i in xrange(0, len(keyzones)):
        print indent, '"%d": {' % i

        writeKeyZone(indent, keyzones[i])

        if i < len(keyzones) - 1:
            print indent, '},'
        else:
            print indent, '}'


def writeKnob(indent, knob):
    print indent, '"Name": "%s",' % (knob['name'] if 'name' in knob else '')
    print indent, '"MIDIType": "3",'
    print indent, '"MIDIId": "%d",' % (knob['number'] if 'number' in knob else 14)
    print indent, '"Channel": "0",'
    print indent, '"Min": "%d",' % knob['min']
    print indent, '"Max": "%d",' % knob['max']
    print indent, '"Inc": "1",'
    print indent, '"Mode": "0"'

def writeKnobs(indent, knobs):
    for i in xrange(0, 8):
        print indent, '"%d": {' % i
        if i < len(knobs):
            writeKnob(indent + INDENT_STEP, knobs[i])
        else:
            # write disabled knob
            writeKnob(indent + INDENT_STEP, {'max':127, 'min':0})
        if i < 7:    
            print indent, '},'
        else:    
            print indent, '}'

def writeButton(indent, button):
    print indent, '"Name": "%s",' % (button['name'] if 'name' in button else '')
    print indent, '"MIDIType": "%d",' %(button['midi_type'] if 'midi_type' in button else 3)
    print indent, '"MIDIId": "%d",' %(button['number'] if 'number' in button else 14)
    print indent, '"Channel": "0",'
    print indent, '"Off": "0",'
    print indent, '"On": "%s",' % (button['on'] if 'on' in button else 127)
    print indent, '"Inc": "0",'
    print indent, '"Behavior": "%d"' % (button['behaviour'] if 'on' in button else 0)

def writeButtons(indent, buttons):
    for i in xrange(0, 8):
        print indent, '"%d": {' % i
        if i < len(buttons):
            writeButton(indent + INDENT_STEP, buttons[i])
        else:
            # write disabled button
            writeButton(indent + INDENT_STEP, {})
        if i < 7:    
            print indent, '},'
        else:    
            print indent, '}'

def addProgramChangeButton(buttons, program_number):
    buttons.append({
        'name': 'Select Prog',
        'midi_type': MIDI_TYPES['program_change'],
        'behaviour': BEHAVIOUR['trigger'],
        'on': program_number
    })

def addControls(buttons, knobs, controls):
    for cc in controls:
        if cc['type'] == 'toggle':
            cc['behaviour'] = BEHAVIOUR['toggle']
            buttons.append(cc)
        elif cc['type'] == 'enum':
            for i in xrange(0, len(cc['enums'])):
                buttons.append({
                    'name': "%s:%s" % (cc['short_name'] if 'short_name' in cc else cc['name'], cc['enums'][i]),
                    'behaviour': BEHAVIOUR['trigger'],
                    'number': cc['number'],
                    'on': cc['values'][i]
                })
        else:
            knobs.append(cc)

def writeTemplate(indent, template, template_index):
    print indent, '"Name": "%s",' % template['name']
    zoneindent = indent + INDENT_STEP
    pageindent = indent + INDENT_STEP
    knobindent = pageindent + INDENT_STEP
    
    print indent, '"keyzones": {'
    writeKeyZones(zoneindent, template['keyzones'])
    print indent, '},'

    buttons = []
    knobs =[]
    addProgramChangeButton(buttons, template_index)
    addControls(buttons, knobs, template['controls'])

    # we need at least one page, even if all buttons are unused on it
    #  or else the Komplete Kontrol app crashes
    num_pages = max(1, (max(len(buttons), len(knobs)) + 7)/8)

    print indent, '"pages": {'
    for i in xrange(0, num_pages):
        print pageindent, '"%d": {' % i

        print knobindent, '"knobs": {'
        writeKnobs(knobindent + INDENT_STEP, knobs)
        print knobindent, '},'

        print knobindent, '"buttons": {'
        writeButtons(knobindent + INDENT_STEP, buttons)
        print knobindent, '}'

        knobs = knobs[8:]
        buttons = buttons[8:]
        
        if i < num_pages - 1:
            print pageindent, '},'
        else:
            print pageindent, '}'

    print indent, '}'

def writeTemplates(indent, progs):
    print indent, '"templates": {'
    newindent = indent + INDENT_STEP
    for i in xrange(0, len(progs)):
        print newindent, '"%d": {' % i
        writeTemplate(newindent + INDENT_STEP, progs[i], i)
        if i < len(progs) - 1:
            print newindent, "},"
        else:
            print newindent, "}"
    print indent, "},"

def writeDatFile(progs):
    print "{"
    indent = INDENT_STEP
    print indent, '"Version": "4",'
    print indent, '"ActiveTemplateIndex": "0",'
    print indent, '"VelocityCurve": "3",'
    writeTemplates(indent, progs)
    print '    "pedals": { \n\
        "pedalA": {\n\
            "MIDIType": "3",\n\
            "MIDIId": "11",\n\
            "Channel": "0",\n\
            "Min": "0",\n\
            "Max": "127"\n\
        },\n\
        "pedalConfigA": {\n\
            "ContiniuousMode": "false",\n\
            "Invert": "false",\n\
            "SwapTR": "false"\n\
        },\n\
        "fsTipA": {\n\
            "MIDIType": "3",\n\
            "MIDIId": "64",\n\
            "Channel": "0",\n\
            "Off": "0",\n\
            "On": "127",\n\
            "Inc": "1",\n\
            "Behavior": "2"\n\
        },\n\
        "fsRingA": {\n\
            "MIDIType": "3",\n\
            "MIDIId": "65",\n\
            "Channel": "0",\n\
            "Off": "0",\n\
            "On": "127",\n\
            "Inc": "1",\n\
            "Behavior": "2"\n\
        },\n\
        "pedalB": {\n\
            "MIDIType": "3",\n\
            "MIDIId": "11",\n\
            "Channel": "0",\n\
            "Min": "0",\n\
            "Max": "127"\n\
        },\n\
        "pedalConfigB": {\n\
            "ContiniuousMode": "true",\n\
            "Invert": "false",\n\
            "SwapTR": "false"\n\
        },\n\
        "fsTipB": {\n\
            "MIDIType": "3",\n\
            "MIDIId": "64",\n\
            "Channel": "0",\n\
            "Off": "0",\n\
            "On": "127",\n\
            "Inc": "1",\n\
            "Behavior": "2"\n\
        },\n\
        "fsRingB": {\n\
            "MIDIType": "3",\n\
            "MIDIId": "65",\n\
            "Channel": "0",\n\
            "Off": "0",\n\
            "On": "127",\n\
            "Inc": "1",\n\
            "Behavior": "2"\n\
        }\n\
    },\n\
    "touchstrip": {\n\
        "MIDIType": "3",\n\
        "MIDIId": "7",\n\
        "Channel": "0",\n\
        "Min": "0",\n\
        "Max": "127",\n\
        "Param1": "4",\n\
        "CenterValue": "0",\n\
        "PhysicsModel": "0"\n\
    }'
    print "}"


writeDatFile(programs.get())

#for i in xrange(0, len(programs)):
#    print programs[i]['program']

