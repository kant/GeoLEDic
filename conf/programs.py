programs = [
    {
        'program':'DefaultRainbow',
        'name':'Default Rainbow',
        'base': 'Notes',
        'controls': [
            {
                'name': 'Speed',
                'number': 16,
            },
            {
                'name': 'Stride',
                'number': 17,
            },
            {
                'name': 'Sparkle Probability',
                'number': 19,
            }
        ]
    },
    {
        'program':'SparklesAndTriangles',
        'name':'Sparkles and Triangles',
        'base': 'ShapesFromNotes',
        'keyzones' : [
            {
                'name': 'Pentagon 0',
                'from': 12,
                'to': 17,
                'channel': 1,
                'transpose': 24
            },
            {
                'name': 'Pentagon 1',
                'from': 24,
                'to': 33,
                'channel': 1,
                'transpose': 24
            },
            {
                'name': 'Pentagon 2',
                'from': 36,
                'to': 42,
                'channel': 1,
                'transpose': 24
            },
            {
                'name': 'Pentagon 3',
                'from': 48,
                'to': 57,
                'channel': 1,
                'transpose': 24
            },
            {
                'name': 'blobs',
                'from': 60,
                'to': 111,
                'channel': 2,
                'transpose': -24
            }

        ],
        'controls': [
            {
                'name': 'Red Worm',
                'number': 16,
            },
            {
                'name': 'Green Worm',
                'number': 17,
            },
            {
                'name': 'Blue Worm',
                'number': 18,
            },
            {
                'name': 'Sparkle Probability',
                'number': 19,
            }
        ]
    },
    {
        'program':'Fire',
        'base': 'Notes',
        'controls': [
            {
                'name': 'Cooling',
                'number': 16
            },
            {
                'name': 'Sparking',
                'number': 17
            },
            {
                'name': 'Downwards',
                'number': 19,
                'type': 'toggle'
            },
            {
                'name': 'Reverse Palette',
                'number': 20,
                'type': 'toggle'
            },
            {
                'name': 'Palette',
                'short_name': 'Pal',
                'type': 'enum',
                'number': 18,
                'enums': [
                    'Fire',
                    'Ocean',
                    'Cloud',
                    'Forest',
                    'Lava',
                    'Rainbow',
                    'Party'
                ]
            }
        ]

    },
    {
        'program':'MovingRainbow',
        'name':'Moving Rainbow',
        'base': 'Notes',
        'controls': [
            {
                'name': 'Speed Vertical',
                'number': 16,
            },
            {
                'name': 'Stride Vertical',
                'number': 17,
            },
            {
                'name': 'Speed Horizontal',
                'number': 18,
            },
            {
                'name': 'Stride Horizontal',
                'number': 19,
            }
        ]
    },
    {
        'program':'Lightning',
        'base': 'Notes',
        'controls': [
            {
                'name': 'Lightning Probability',
                'number': 16,
            },
            {
                'name': 'Forking Probability',
                'number': 17,
            }
        ]
    }
]



def get():    
    # fill in defaults and expand values where needed (e.g. enums)
    for i in range(0, len(programs)):

        if not 'name' in programs[i]:
            programs[i]['name'] = programs[i]['program']

        if not 'keyzones' in programs[i]:
            programs[i]['keyzones'] = []

        if not 'controls' in programs[i]:
            programs[i]['controls'] = []
        else:
            for cc in programs[i]['controls']:
                if not 'type' in cc:
                    cc['type'] = 'continuous'
                if cc['type'] == 'enum':
                    # spread enum values on range 0..127 to make it easier to use them with a knob
                    n = len(cc['enums'])
                    cc['values'] = range(0, n*int(127/n), int(127/n))
    return programs