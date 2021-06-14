import math
import sys

fbase = sys.argv[1]+"/Dome"

row0 = [
    [ 5.104,  2.683, 1.658],
    [ 5.706,  1.854, 0.000],
    [ 5.706,  0.829, 1.658],
    [ 6.000,  0.000, 0.000],
    [ 5.733, -0.931, 1.507],
    [ 5.706, -1.854, 0.000],
    [ 5.185, -2.616, 1.507],
    [ 4.854, -3.527, 0.000],
    [ 4.129, -4.025, 1.658],
    [ 3.527, -4.854, 0.000],
    [ 2.552, -5.171, 1.658],
    [ 1.854, -5.706, 0.000],
    [ 0.886, -5.740, 1.507],
    [ 0.000, -6.000, 0.000],
    [-0.886, -5.740, 1.507],
    [-1.854, -5.706, 0.000],
    [-2.552, -5.171, 1.658],
    [-3.527, -4.854, 0.000],
    [-4.129, -4.025, 1.658],
    [-4.854, -3.527, 0.000],
    [-5.185, -2.616, 1.507],
    [-5.706, -1.854, 0.000],
    [-5.733, -0.931, 1.507],
    [-6.000,  0.000, 0.000],
    [-5.706,  0.829, 1.658],
    [-5.706,  1.854, 0.000],
    [-5.104,  2.683, 1.658]

]

row1 = [
    [ 4.090,  3.192, 3.014],
    [ 5.104,  2.683, 1.658],
    [ 4.854,  1.577, 3.154],
    [ 5.706,  0.829, 1.658],
    [ 5.185, -0.178, 3.014],
    [ 5.733, -0.931, 1.507],
    [ 5.104, -1.658, 2.683],
    [ 5.185, -2.616, 1.507],
    [ 4.299, -2.904, 3.014],
    [ 4.129, -4.025, 1.658],
    [ 3.000, -4.129, 3.154],
    [ 2.552, -5.171, 1.658],
    [ 1.433, -4.986, 3.014],
    [ 0.886, -5.740, 1.507],
    [ 0.000, -5.367, 2.683],
    [-0.886, -5.740, 1.507],
    [-1.433, -4.986, 3.014],
    [-2.552, -5.171, 1.658],
    [-3.000, -4.129, 3.154],
    [-4.129, -4.025, 1.658],
    [-4.299, -2.904, 3.014],
    [-5.185, -2.616, 1.507],
    [-5.104, -1.658, 2.683],
    [-5.733, -0.931, 1.507],
    [-5.185, -0.178, 3.014],
    [-5.706,  0.829, 1.658],
    [-4.854,  1.577, 3.154],
    [-5.104,  2.683, 1.658],
    [-4.090,  3.192, 3.014]
]

row20 = [
    [ 2.657,  3.657, 3.945],
    [ 4.090,  3.192, 3.014],
    [ 3.527,  2.171, 4.342],
    [ 4.854,  1.577, 3.154],
    [ 4.129,  0.317, 4.342],
    [ 5.185, -0.178, 3.014],
    [ 4.299, -1.397, 3.945],
    [ 5.104, -1.658, 2.683]
]

row21 = [
    [ 5.104, -1.658, 2.683],
    [ 4.299, -1.397, 3.945],
    [ 4.299, -2.904, 3.014],
    [ 3.154, -2.683, 4.342],
    [ 3.000, -4.129, 3.154],
    [ 1.577, -3.829, 4.342],
    [ 1.433, -4.986, 3.014],
    [ 0.000, -4.521, 3.945],  
    [ 0.000, -5.367, 2.683]
]

row22 = [
    [-0.000, -5.367, 2.683],
    [-0.000, -4.521, 3.945],
    [-1.433, -4.986, 3.014],
    [-1.577, -3.829, 4.342],
    [-3.000, -4.129, 3.154],
    [-3.154, -2.683, 4.342],
    [-4.299, -2.904, 3.014],
    [-4.299, -1.397, 3.945],
    [-5.104, -1.658, 2.683]
]

row23 = [
    [-5.104, -1.658, 2.683],
    [-4.299, -1.397, 3.945],
    [-5.185, -0.178, 3.014],
    [-4.129,  0.317, 4.342],
    [-4.854,  1.577, 3.154],
    [-3.527,  2.171, 4.342],
    [-4.090,  3.192, 3.014],
    [-2.657,  3.657, 3.945]
]

row30 = [
    [ 0.975,  4.025, 4.342],
    [ 2.657,  3.657, 3.945],
    [ 1.854,  2.552, 5.104],
    [ 3.527,  2.171, 4.342],
    [ 2.552,  0.829, 5.367],
    [ 4.129,  0.317, 4.342],
    [ 3.000, -0.975, 5.104],
    [ 4.299, -1.397, 3.945]
]

row31 = [
    [ 4.299, -1.397, 3.945],
    [ 3.000, -0.975, 5.104],
    [ 3.154, -2.683, 4.342],
    [ 1.577, -2.171, 5.367],
    [ 1.577, -3.829, 4.342],
    [ 0.000, -3.154, 5.104],
    [ 0.000, -4.521, 3.945]
]

row32 = [
    [-0.000, -4.521, 3.945],  
    [-0.000, -3.154, 5.104],
    [-1.577, -3.829, 4.342],
    [-1.577, -2.171, 5.367],
    [-3.154, -2.683, 4.342],
    [-3.000, -0.975, 5.104],
    [-4.299, -1.397, 3.945]
]

row33 = [
    [-4.299, -1.397, 3.945],
    [-3.000, -0.975, 5.104],
    [-4.129,  0.317, 4.342],
    [-2.552,  0.829, 5.367],
    [-3.527,  2.171, 4.342],
    [-1.854,  2.552, 5.104],
    [-2.657,  3.657, 3.945],
    [-0.975,  4.025, 4.342]

]

row34 = [
    [-1.854,  2.552, 5.104],
    [-0.975,  4.025, 4.342],
    [ 0.000,  2.683, 5.367],
    [ 0.975,  4.025, 4.342],
    [ 1.854,  2.552, 5.104]
]

row40 = [
    [ 0.000,  2.683, 5.367],
    [ 1.854,  2.552, 5.104],
    [ 0.886,  1.219, 5.808],
    [ 2.552,  0.829, 5.367],
    [ 1.433, -0.466, 5.808],
    [ 3.000, -0.975, 5.104]
]

row41 = [
    [ 3.000, -0.975, 5.104],
    [ 1.433, -0.466, 5.808],
    [ 1.577, -2.171, 5.367],
    [ 0.000, -1.507, 5.808],
    [ 0.000, -3.154, 5.104]    
]

row42 = [
    [-0.000, -3.154, 5.104],
    [-0.000, -1.507, 5.808],
    [-1.577, -2.171, 5.367],
    [-1.433, -0.466, 5.808],
    [-3.000, -0.975, 5.104]
]

row43 = [
    [-3.000, -0.975, 5.104],
    [-1.433, -0.466, 5.808],
    [-2.552,  0.829, 5.367],
    [-0.886,  1.219, 5.808],
    [-1.854,  2.552, 5.104]
]

row44 = [
    [-1.854,  2.552, 5.104],
    [-0.886,  1.219, 5.808],
    [ 0.000,  2.683, 5.367],
    [ 0.886,  1.219, 5.808]
]

row50 = [
    [-0.886,  1.219, 5.808],
    [ 0.886,  1.219, 5.808],
    [ 0.000,  0.000, 6.000],
    [ 1.433, -0.466, 5.808]
]

row51 = [
    [ 1.433, -0.466, 5.808],
    [ 0.000, -1.507, 5.808],
    [ 0.000,  0.000, 6.000],
    [-1.433, -0.466, 5.808],
    [-0.886,  1.219, 5.808]
]

# map exterior panel edge lengths of the (inaccurate) SketchUp model to the
# actual strut lengths
strut_map = {
   1.519: 1.155, # A  20
   1.771: 1.380, # B  22
   1.767: 1.677, # C  48
   1.877: 1.700, # D  54
   1.950: 1.772, # E  27
   1.792: 1.799, # F? 24
}

strips = [
   [  0,   1,   2,  29],
   [  3,   4,   5,  30],
   [  6,   7,   8,  31],
   [  9,  10,  36,  37],
   [ 11,  12,  13,  38],
   [ 14,  15,  16,  39],
   [ 17,  18,  44,  45],
   [ 19,  20,  21,  46],
   [ 22,  23,  24,  47],
   [ 25,  26,  27,  28],
   [ 32,  33,  34,  35],
   [ 40,  41,  42,  43],
   [ 48,  49,  50,  51],
   [ 52,  53,  78,  79],
   [ 54,  55,  56,  57],
   [ 58,  59,  83,  84],
   [ 60,  61,  62,  64],
   [ 63,  66,  88,  89],
   [ 65,  67,  68,  69],
   [ 70,  71,  93,  94],
   [ 72,  73,  74,  75],
   [ 76,  77,  98,  99],
   [ 80,  81,  82],
   [ 85,  86,  87],
   [ 90,  91,  92],
   [ 95,  96,  97],
   [100, 101, 102],
   [103, 104, 117, 118],
   [105, 106, 107, 119],
   [108, 109, 110, 120],
   [111, 112, 113, 121],
   [114, 115, 116, 122]
]

led_counts = [0] * 32


def distance(a, b):
   global strut_map
   e = [b[0] - a[0], b[1] - a[1], b[2] - a[2]]
   panel_edge_length =  math.sqrt(e[0]**2 + e[1]**2 + e[2]**2)
   min_diff = 10000;
   strut_length = 0;
   for outer, strut in strut_map.items():
      d = abs(outer - panel_edge_length)
      if d < min_diff:
         min_diff = d
         strut_length = strut
   if (strut_length == 0):
      raise Exception("Couldn't find strut length for outer panel edge %.3f" % panel_edge_length)
   return strut_length

total_length = 0
triangle_ix = 0

def find_strip(triangle_ix):
   global strips
   for k in xrange(len(strips)):
      if triangle_ix in strips[k]:
         return k
   raise Exception("Couldn't find strip for triangle %d" % triangle_ix)
         

def rotate180(triangle):
   for c in triangle:
      c[0] = -c[0]
      c[2] = -c[2]

def angle(coords):
   if (coords[0] == 0 and coords[2] == 0):
      # at the apex, artificially high number to make sure it isn't the starting corner
      return 100
   return round(2*math.atan2(coords[0], -coords[2]),3)/2

def print_row(row):
    global total_length
    global triangle_ix
    global led_counts

    for k in xrange(len(row)-2):
        s = []
        
        triangle = []
        for m in xrange(3):
            # Note: Sketchup order of coordinates is x/z/y, so we'll reorder here
            #       Also, the x coordinate seems mirrored
            triangle.append([-row[k+m][0], row[k+m][2], row[k+m][1]])

        # rotate by 180 deg if necessary to steer clear of the singularity at +-pi
        triangle_rotated = abs(angle(triangle[0])) > math.pi*3/4
        if triangle_rotated:
            rotate180(triangle)

        # make triangles turn clock-wise:
        # first corner is left-most (lowest horizontal angle, lowest y if angle equal), second corner is top-most (highest y)
        triangle.sort(key=lambda c: (angle(c), c[1]))

        # second corner is the one higher up of the two remaining
        if triangle[1][1] < triangle[2][1]:
            tmp = triangle[2]
            triangle[2] = triangle[1]
            triangle[1] = tmp

        if triangle_rotated:
            rotate180(triangle)

        for m in xrange(3):
            s.append("{{ {:6.3f}, {:6.3f}, {:6.3f} }}".format(triangle[m][0], triangle[m][1], triangle[m][2]))

        edge_lengths = [distance(triangle[0], triangle[1]),
                        distance(triangle[1], triangle[2]),
                        distance(triangle[2], triangle[0])]
        triangle_length = sum(edge_lengths)
        total_length += triangle_length
        num_leds = int(math.ceil(triangle_length*60)) + 3 # adding 3 LEDs for the corners seems to be roughly right
        comment = "// {:.3f}, {:.3f}, {:.3f}: {:.4f}m (~{:d} LEDs)".format(edge_lengths[0], edge_lengths[1], edge_lengths[2], triangle_length, num_leds)
        vertices = ', '.join(s)
        strip_ix = find_strip(triangle_ix)
        edges_def = []
        leds_remaining = num_leds
        for e in xrange(3):
           start = led_counts[strip_ix]
           if e < 2:
              leds_on_edge = math.ceil(edge_lengths[e] * 60)
              leds_remaining -= leds_on_edge
           else:
              leds_on_edge = leds_remaining
           end   = start + leds_on_edge - 1
           led_counts[strip_ix] += leds_on_edge
           edges_def.append("           {%4d, %4d}" % (start, end))
        triangle_def = "strip(%2d), {%s}" % (strip_ix, ', '.join(edges_def))
        print "/* %3d */ { %s,   {%s}}, %s" % (triangle_ix, triangle_def, vertices, comment)
        triangle_ix += 1
        
def printHeader():
    print("/* triangle   strip             LEDs on 1st edge         LEDs on 2nd edge          LEDs on 3rd edge      coordinates 1st corner      coordinates 2nd corner      coordinates 3rd corner  */")

with open(fbase + ".cpp", 'w') as f:
   original_stdout = sys.stdout
   sys.stdout = f
   print "#include \"Dome.hpp\""
   print ""
   print "CRGB leds[NUM_STRIPS * LEDS_PER_STRIP];"
   print ""
   print "namespace {"
   print "CRGB* strip(int ix){ return &leds[ix*LEDS_PER_STRIP]; }"
   print "}"
   print ""
   print "Triangle dome[DOME_NUM_TRIANGLES] = {"
   print "// row 0"
   printHeader()
   print_row(row0)
   print "// row 1"
   printHeader()
   print_row(row1)
   print "// row 2"
   printHeader()
   print_row(row20)
   print_row(row21)
   print_row(row22)
   print_row(row23)
   print "// row 3"
   printHeader()
   print_row(row30)
   print_row(row31)
   print_row(row32)
   print_row(row33)
   print_row(row34)
   print "// row 4"
   printHeader()
   print_row(row40)
   print_row(row41)
   print_row(row42)
   print_row(row43)
   print_row(row44)
   print "// row 5"
   printHeader()
   print_row(row50)
   print_row(row51)
   print "};"
   sys.stdout = original_stdout

with open(fbase + ".hpp", 'w') as f:
   original_stdout = sys.stdout
   sys.stdout = f
   print \
   "#ifndef GEOLEDIC_DOME_HPP\n" \
   "#define GEOLEDIC_DOME_HPP\n" \
   "\n" \
   "#include \"Triangle.hpp\"\n" \
   "\n" \
   "#define DOME_NUM_TRIANGLES 123\n" \
   "#define NUM_STRIPS %d\n" \
   "#define LEDS_PER_STRIP %d\n" \
   "\n" \
   "extern CRGB leds[NUM_STRIPS * LEDS_PER_STRIP];\n" \
   "extern Triangle dome[DOME_NUM_TRIANGLES];" \
   "\n" \
   "#endif\n" % (len(led_counts), max(led_counts))
   sys.stdout = original_stdout
