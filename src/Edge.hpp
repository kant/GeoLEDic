#ifndef GEOLEDIC_EDGE_HPP
#define GEOLEDIC_EDGE_HPP

struct Edge {
   Edge(): first_led(), last_led()
   {}
   Edge(int first_led, int last_led): first_led(first_led), last_led(last_led)
   {}
   int first_led;
   int last_led;
};


#endif
