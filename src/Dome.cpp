#include "Dome.hpp"

CRGB strips[NUM_STRIPS * LEDS_PER_STRIP];

Triangle dome[DOME_NUM_TRIANGLES] = {
// row 0
/*   0 */ { &strips[ 0*LEDS_PER_STRIP], {{   0,  112}, { 113,  225}, { 226,  338}},  {{ -5.104,  1.658,  2.683 }, { -5.706,  0.000,  1.854 }, { -5.706,  1.658,  0.829 }}}, // 0: 1.881, 1.881, 1.881: 5.6420m (~339 LEDs)
/*   1 */ { &strips[ 0*LEDS_PER_STRIP], {{ 339,  451}, { 452,  560}, { 561,  668}},  {{ -5.706,  0.000,  1.854 }, { -5.706,  1.658,  0.829 }, { -6.000,  0.000,  0.000 }}}, // 1: 1.881, 1.808, 1.809: 5.4978m (~330 LEDs)
/*   2 */ { &strips[ 0*LEDS_PER_STRIP], {{ 669,  777}, { 778,  881}, { 882,  982}},  {{ -5.706,  1.658,  0.829 }, { -6.000,  0.000,  0.000 }, { -5.733,  1.507, -0.931 }}}, // 2: 1.808, 1.723, 1.698: 5.2294m (~314 LEDs)
/*   3 */ { &strips[ 1*LEDS_PER_STRIP], {{   0,  103}, { 104,  205}, { 206,  313}},  {{ -6.000,  0.000,  0.000 }, { -5.733,  1.507, -0.931 }, { -5.706,  0.000, -1.854 }}}, // 3: 1.723, 1.699, 1.809: 5.2305m (~314 LEDs)
/*   4 */ { &strips[ 1*LEDS_PER_STRIP], {{ 314,  415}, { 416,  517}, { 518,  620}},  {{ -5.733,  1.507, -0.931 }, { -5.706,  0.000, -1.854 }, { -5.185,  1.507, -2.616 }}}, // 4: 1.699, 1.699, 1.703: 5.1010m (~307 LEDs)
/*   5 */ { &strips[ 1*LEDS_PER_STRIP], {{ 621,  722}, { 723,  826}, { 827,  934}},  {{ -5.706,  0.000, -1.854 }, { -5.185,  1.507, -2.616 }, { -4.854,  0.000, -3.527 }}}, // 5: 1.699, 1.723, 1.809: 5.2310m (~314 LEDs)
/*   6 */ { &strips[ 2*LEDS_PER_STRIP], {{   0,  103}, { 104,  212}, { 213,  313}},  {{ -5.185,  1.507, -2.616 }, { -4.854,  0.000, -3.527 }, { -4.129,  1.658, -4.025 }}}, // 6: 1.723, 1.808, 1.699: 5.2304m (~314 LEDs)
/*   7 */ { &strips[ 2*LEDS_PER_STRIP], {{ 314,  422}, { 423,  535}, { 536,  643}},  {{ -4.854,  0.000, -3.527 }, { -4.129,  1.658, -4.025 }, { -3.527,  0.000, -4.854 }}}, // 7: 1.808, 1.881, 1.808: 5.4970m (~330 LEDs)
/*   8 */ { &strips[ 2*LEDS_PER_STRIP], {{ 644,  756}, { 757,  869}, { 870,  982}},  {{ -4.129,  1.658, -4.025 }, { -3.527,  0.000, -4.854 }, { -2.552,  1.658, -5.171 }}}, // 8: 1.881, 1.881, 1.881: 5.6423m (~339 LEDs)
/*   9 */ { &strips[ 3*LEDS_PER_STRIP], {{   0,  112}, { 113,  221}, { 222,  329}},  {{ -3.527,  0.000, -4.854 }, { -2.552,  1.658, -5.171 }, { -1.854,  0.000, -5.706 }}}, // 9: 1.881, 1.808, 1.809: 5.4981m (~330 LEDs)
/*  10 */ { &strips[ 3*LEDS_PER_STRIP], {{ 330,  438}, { 439,  542}, { 543,  643}},  {{ -2.552,  1.658, -5.171 }, { -1.854,  0.000, -5.706 }, { -0.886,  1.507, -5.740 }}}, // 10: 1.808, 1.723, 1.698: 5.2297m (~314 LEDs)
/*  11 */ { &strips[ 4*LEDS_PER_STRIP], {{   0,  103}, { 104,  205}, { 206,  313}},  {{ -1.854,  0.000, -5.706 }, { -0.886,  1.507, -5.740 }, { -0.000,  0.000, -6.000 }}}, // 11: 1.723, 1.699, 1.809: 5.2305m (~314 LEDs)
/*  12 */ { &strips[ 4*LEDS_PER_STRIP], {{ 314,  415}, { 416,  517}, { 518,  620}},  {{ -0.886,  1.507, -5.740 }, { -0.000,  0.000, -6.000 }, {  0.886,  1.507, -5.740 }}}, // 12: 1.699, 1.699, 1.704: 5.1013m (~307 LEDs)
/*  13 */ { &strips[ 4*LEDS_PER_STRIP], {{ 621,  722}, { 723,  826}, { 827,  934}},  {{ -0.000,  0.000, -6.000 }, {  0.886,  1.507, -5.740 }, {  1.854,  0.000, -5.706 }}}, // 13: 1.699, 1.723, 1.809: 5.2305m (~314 LEDs)
/*  14 */ { &strips[ 5*LEDS_PER_STRIP], {{   0,  103}, { 104,  212}, { 213,  313}},  {{  0.886,  1.507, -5.740 }, {  1.854,  0.000, -5.706 }, {  2.552,  1.658, -5.171 }}}, // 14: 1.723, 1.808, 1.698: 5.2297m (~314 LEDs)
/*  15 */ { &strips[ 5*LEDS_PER_STRIP], {{ 314,  422}, { 423,  535}, { 536,  643}},  {{  1.854,  0.000, -5.706 }, {  2.552,  1.658, -5.171 }, {  3.527,  0.000, -4.854 }}}, // 15: 1.808, 1.881, 1.809: 5.4981m (~330 LEDs)
/*  16 */ { &strips[ 5*LEDS_PER_STRIP], {{ 644,  756}, { 757,  869}, { 870,  982}},  {{  2.552,  1.658, -5.171 }, {  3.527,  0.000, -4.854 }, {  4.129,  1.658, -4.025 }}}, // 16: 1.881, 1.881, 1.881: 5.6423m (~339 LEDs)
/*  17 */ { &strips[ 6*LEDS_PER_STRIP], {{   0,  112}, { 113,  221}, { 222,  329}},  {{  3.527,  0.000, -4.854 }, {  4.129,  1.658, -4.025 }, {  4.854,  0.000, -3.527 }}}, // 17: 1.881, 1.808, 1.808: 5.4970m (~330 LEDs)
/*  18 */ { &strips[ 6*LEDS_PER_STRIP], {{ 330,  438}, { 439,  542}, { 543,  643}},  {{  4.129,  1.658, -4.025 }, {  4.854,  0.000, -3.527 }, {  5.185,  1.507, -2.616 }}}, // 18: 1.808, 1.723, 1.699: 5.2304m (~314 LEDs)
/*  19 */ { &strips[ 7*LEDS_PER_STRIP], {{   0,  103}, { 104,  205}, { 206,  313}},  {{  4.854,  0.000, -3.527 }, {  5.185,  1.507, -2.616 }, {  5.706,  0.000, -1.854 }}}, // 19: 1.723, 1.699, 1.809: 5.2310m (~314 LEDs)
/*  20 */ { &strips[ 7*LEDS_PER_STRIP], {{ 314,  415}, { 416,  517}, { 518,  620}},  {{  5.185,  1.507, -2.616 }, {  5.706,  0.000, -1.854 }, {  5.733,  1.507, -0.931 }}}, // 20: 1.699, 1.699, 1.703: 5.1010m (~307 LEDs)
/*  21 */ { &strips[ 7*LEDS_PER_STRIP], {{ 621,  722}, { 723,  826}, { 827,  934}},  {{  5.706,  0.000, -1.854 }, {  5.733,  1.507, -0.931 }, {  6.000,  0.000,  0.000 }}}, // 21: 1.699, 1.723, 1.809: 5.2305m (~314 LEDs)
/*  22 */ { &strips[ 8*LEDS_PER_STRIP], {{   0,  103}, { 104,  212}, { 213,  313}},  {{  5.733,  1.507, -0.931 }, {  6.000,  0.000,  0.000 }, {  5.706,  1.658,  0.829 }}}, // 22: 1.723, 1.808, 1.698: 5.2294m (~314 LEDs)
/*  23 */ { &strips[ 8*LEDS_PER_STRIP], {{ 314,  422}, { 423,  535}, { 536,  643}},  {{  6.000,  0.000,  0.000 }, {  5.706,  1.658,  0.829 }, {  5.706,  0.000,  1.854 }}}, // 23: 1.808, 1.881, 1.809: 5.4978m (~330 LEDs)
/*  24 */ { &strips[ 8*LEDS_PER_STRIP], {{ 644,  756}, { 757,  869}, { 870,  982}},  {{  5.706,  1.658,  0.829 }, {  5.706,  0.000,  1.854 }, {  5.104,  1.658,  2.683 }}}, // 24: 1.881, 1.881, 1.881: 5.6420m (~339 LEDs)
// row 1
/*  25 */ { &strips[ 9*LEDS_PER_STRIP], {{   0,  101}, { 102,  210}, { 211,  313}},  {{ -4.090,  3.014,  3.192 }, { -5.104,  1.658,  2.683 }, { -4.854,  3.154,  1.577 }}}, // 25: 1.700, 1.809, 1.724: 5.2318m (~314 LEDs)
/*  26 */ { &strips[ 9*LEDS_PER_STRIP], {{ 314,  422}, { 423,  531}, { 532,  643}},  {{ -5.104,  1.658,  2.683 }, { -4.854,  3.154,  1.577 }, { -5.706,  1.658,  0.829 }}}, // 26: 1.809, 1.809, 1.881: 5.4980m (~330 LEDs)
/*  27 */ { &strips[ 9*LEDS_PER_STRIP], {{ 644,  752}, { 753,  854}, { 855,  957}},  {{ -4.854,  3.154,  1.577 }, { -5.706,  1.658,  0.829 }, { -5.185,  3.014, -0.178 }}}, // 27: 1.809, 1.699, 1.723: 5.2305m (~314 LEDs)
/*  28 */ { &strips[ 9*LEDS_PER_STRIP], {{ 958, 1059}, {1060, 1162}, {1163, 1264}},  {{ -5.706,  1.658,  0.829 }, { -5.185,  3.014, -0.178 }, { -5.733,  1.507, -0.931 }}}, // 28: 1.699, 1.703, 1.698: 5.1003m (~307 LEDs)
/*  29 */ { &strips[ 0*LEDS_PER_STRIP], {{ 983, 1085}, {1086, 1173}, {1174, 1259}},  {{ -5.185,  3.014, -0.178 }, { -5.733,  1.507, -0.931 }, { -5.104,  2.683, -1.658 }}}, // 29: 1.703, 1.450, 1.450: 4.6037m (~277 LEDs)
/*  30 */ { &strips[ 1*LEDS_PER_STRIP], {{ 935, 1022}, {1023, 1110}, {1111, 1211}},  {{ -5.733,  1.507, -0.931 }, { -5.104,  2.683, -1.658 }, { -5.185,  1.507, -2.616 }}}, // 30: 1.450, 1.450, 1.703: 4.6043m (~277 LEDs)
/*  31 */ { &strips[ 2*LEDS_PER_STRIP], {{ 983, 1070}, {1071, 1173}, {1174, 1259}},  {{ -5.104,  2.683, -1.658 }, { -5.185,  1.507, -2.616 }, { -4.299,  3.014, -2.904 }}}, // 31: 1.450, 1.703, 1.451: 4.6051m (~277 LEDs)
/*  32 */ { &strips[10*LEDS_PER_STRIP], {{   0,  102}, { 103,  204}, { 205,  306}},  {{ -5.185,  1.507, -2.616 }, { -4.299,  3.014, -2.904 }, { -4.129,  1.658, -4.025 }}}, // 32: 1.703, 1.699, 1.699: 5.1010m (~307 LEDs)
/*  33 */ { &strips[10*LEDS_PER_STRIP], {{ 307,  408}, { 409,  517}, { 518,  620}},  {{ -4.299,  3.014, -2.904 }, { -4.129,  1.658, -4.025 }, { -3.000,  3.154, -4.129 }}}, // 33: 1.699, 1.809, 1.722: 5.2301m (~314 LEDs)
/*  34 */ { &strips[10*LEDS_PER_STRIP], {{ 621,  729}, { 730,  838}, { 839,  950}},  {{ -4.129,  1.658, -4.025 }, { -3.000,  3.154, -4.129 }, { -2.552,  1.658, -5.171 }}}, // 34: 1.809, 1.809, 1.881: 5.4984m (~330 LEDs)
/*  35 */ { &strips[10*LEDS_PER_STRIP], {{ 951, 1059}, {1060, 1161}, {1162, 1264}},  {{ -3.000,  3.154, -4.129 }, { -2.552,  1.658, -5.171 }, { -1.433,  3.014, -4.986 }}}, // 35: 1.809, 1.699, 1.723: 5.2312m (~314 LEDs)
/*  36 */ { &strips[ 3*LEDS_PER_STRIP], {{ 644,  745}, { 746,  848}, { 849,  950}},  {{ -2.552,  1.658, -5.171 }, { -1.433,  3.014, -4.986 }, { -0.886,  1.507, -5.740 }}}, // 36: 1.699, 1.703, 1.698: 5.1009m (~307 LEDs)
/*  37 */ { &strips[ 3*LEDS_PER_STRIP], {{ 951, 1053}, {1054, 1141}, {1142, 1227}},  {{ -1.433,  3.014, -4.986 }, { -0.886,  1.507, -5.740 }, { -0.000,  2.683, -5.367 }}}, // 37: 1.703, 1.450, 1.451: 4.6044m (~277 LEDs)
/*  38 */ { &strips[ 4*LEDS_PER_STRIP], {{ 935, 1022}, {1023, 1110}, {1111, 1211}},  {{ -0.886,  1.507, -5.740 }, { -0.000,  2.683, -5.367 }, {  0.886,  1.507, -5.740 }}}, // 38: 1.450, 1.450, 1.704: 4.6043m (~277 LEDs)
/*  39 */ { &strips[ 5*LEDS_PER_STRIP], {{ 983, 1070}, {1071, 1173}, {1174, 1259}},  {{ -0.000,  2.683, -5.367 }, {  0.886,  1.507, -5.740 }, {  1.433,  3.014, -4.986 }}}, // 39: 1.450, 1.703, 1.451: 4.6044m (~277 LEDs)
/*  40 */ { &strips[11*LEDS_PER_STRIP], {{   0,  102}, { 103,  204}, { 205,  306}},  {{  0.886,  1.507, -5.740 }, {  1.433,  3.014, -4.986 }, {  2.552,  1.658, -5.171 }}}, // 40: 1.703, 1.699, 1.698: 5.1009m (~307 LEDs)
/*  41 */ { &strips[11*LEDS_PER_STRIP], {{ 307,  408}, { 409,  517}, { 518,  620}},  {{  1.433,  3.014, -4.986 }, {  2.552,  1.658, -5.171 }, {  3.000,  3.154, -4.129 }}}, // 41: 1.699, 1.809, 1.723: 5.2312m (~314 LEDs)
/*  42 */ { &strips[11*LEDS_PER_STRIP], {{ 621,  729}, { 730,  838}, { 839,  950}},  {{  2.552,  1.658, -5.171 }, {  3.000,  3.154, -4.129 }, {  4.129,  1.658, -4.025 }}}, // 42: 1.809, 1.809, 1.881: 5.4984m (~330 LEDs)
/*  43 */ { &strips[11*LEDS_PER_STRIP], {{ 951, 1059}, {1060, 1161}, {1162, 1264}},  {{  3.000,  3.154, -4.129 }, {  4.129,  1.658, -4.025 }, {  4.299,  3.014, -2.904 }}}, // 43: 1.809, 1.699, 1.722: 5.2301m (~314 LEDs)
/*  44 */ { &strips[ 6*LEDS_PER_STRIP], {{ 644,  745}, { 746,  848}, { 849,  950}},  {{  4.129,  1.658, -4.025 }, {  4.299,  3.014, -2.904 }, {  5.185,  1.507, -2.616 }}}, // 44: 1.699, 1.703, 1.699: 5.1010m (~307 LEDs)
/*  45 */ { &strips[ 6*LEDS_PER_STRIP], {{ 951, 1053}, {1054, 1141}, {1142, 1227}},  {{  4.299,  3.014, -2.904 }, {  5.185,  1.507, -2.616 }, {  5.104,  2.683, -1.658 }}}, // 45: 1.703, 1.450, 1.451: 4.6051m (~277 LEDs)
/*  46 */ { &strips[ 7*LEDS_PER_STRIP], {{ 935, 1022}, {1023, 1110}, {1111, 1211}},  {{  5.185,  1.507, -2.616 }, {  5.104,  2.683, -1.658 }, {  5.733,  1.507, -0.931 }}}, // 46: 1.450, 1.450, 1.703: 4.6043m (~277 LEDs)
/*  47 */ { &strips[ 8*LEDS_PER_STRIP], {{ 983, 1070}, {1071, 1173}, {1174, 1259}},  {{  5.104,  2.683, -1.658 }, {  5.733,  1.507, -0.931 }, {  5.185,  3.014, -0.178 }}}, // 47: 1.450, 1.703, 1.450: 4.6037m (~277 LEDs)
/*  48 */ { &strips[12*LEDS_PER_STRIP], {{   0,  102}, { 103,  204}, { 205,  306}},  {{  5.733,  1.507, -0.931 }, {  5.185,  3.014, -0.178 }, {  5.706,  1.658,  0.829 }}}, // 48: 1.703, 1.699, 1.698: 5.1003m (~307 LEDs)
/*  49 */ { &strips[12*LEDS_PER_STRIP], {{ 307,  408}, { 409,  517}, { 518,  620}},  {{  5.185,  3.014, -0.178 }, {  5.706,  1.658,  0.829 }, {  4.854,  3.154,  1.577 }}}, // 49: 1.699, 1.809, 1.723: 5.2305m (~314 LEDs)
/*  50 */ { &strips[12*LEDS_PER_STRIP], {{ 621,  729}, { 730,  838}, { 839,  950}},  {{  5.706,  1.658,  0.829 }, {  4.854,  3.154,  1.577 }, {  5.104,  1.658,  2.683 }}}, // 50: 1.809, 1.809, 1.881: 5.4980m (~330 LEDs)
/*  51 */ { &strips[12*LEDS_PER_STRIP], {{ 951, 1059}, {1060, 1161}, {1162, 1264}},  {{  4.854,  3.154,  1.577 }, {  5.104,  1.658,  2.683 }, {  4.090,  3.014,  3.192 }}}, // 51: 1.809, 1.700, 1.724: 5.2318m (~314 LEDs)
// row 2
/*  52 */ { &strips[13*LEDS_PER_STRIP], {{   0,  102}, { 103,  204}, { 205,  305}},  {{ -2.657,  3.945,  3.657 }, { -4.090,  3.014,  3.192 }, { -3.527,  4.342,  2.171 }}}, // 52: 1.703, 1.699, 1.699: 5.0998m (~306 LEDs)
/*  53 */ { &strips[13*LEDS_PER_STRIP], {{ 306,  407}, { 408,  516}, { 517,  619}},  {{ -4.090,  3.014,  3.192 }, { -3.527,  4.342,  2.171 }, { -4.854,  3.154,  1.577 }}}, // 53: 1.699, 1.809, 1.724: 5.2313m (~314 LEDs)
/*  54 */ { &strips[14*LEDS_PER_STRIP], {{   0,  108}, { 109,  217}, { 218,  329}},  {{ -3.527,  4.342,  2.171 }, { -4.854,  3.154,  1.577 }, { -4.129,  4.342,  0.317 }}}, // 54: 1.809, 1.809, 1.881: 5.4987m (~330 LEDs)
/*  55 */ { &strips[14*LEDS_PER_STRIP], {{ 330,  438}, { 439,  540}, { 541,  643}},  {{ -4.854,  3.154,  1.577 }, { -4.129,  4.342,  0.317 }, { -5.185,  3.014, -0.178 }}}, // 55: 1.809, 1.699, 1.723: 5.2307m (~314 LEDs)
/*  56 */ { &strips[14*LEDS_PER_STRIP], {{ 644,  745}, { 746,  848}, { 849,  950}},  {{ -4.129,  4.342,  0.317 }, { -5.185,  3.014, -0.178 }, { -4.299,  3.945, -1.397 }}}, // 56: 1.699, 1.703, 1.699: 5.1008m (~307 LEDs)
/*  57 */ { &strips[14*LEDS_PER_STRIP], {{ 951, 1053}, {1054, 1141}, {1142, 1227}},  {{ -5.185,  3.014, -0.178 }, { -4.299,  3.945, -1.397 }, { -5.104,  2.683, -1.658 }}}, // 57: 1.703, 1.451, 1.450: 4.6041m (~277 LEDs)
/*  58 */ { &strips[15*LEDS_PER_STRIP], {{   0,   87}, {  88,  190}, { 191,  276}},  {{ -5.104,  2.683, -1.658 }, { -4.299,  3.945, -1.397 }, { -4.299,  3.014, -2.904 }}}, // 58: 1.451, 1.703, 1.451: 4.6053m (~277 LEDs)
/*  59 */ { &strips[15*LEDS_PER_STRIP], {{ 277,  379}, { 380,  481}, { 482,  583}},  {{ -4.299,  3.945, -1.397 }, { -4.299,  3.014, -2.904 }, { -3.154,  4.342, -2.683 }}}, // 59: 1.703, 1.699, 1.699: 5.1003m (~307 LEDs)
/*  60 */ { &strips[16*LEDS_PER_STRIP], {{   0,  101}, { 102,  210}, { 211,  313}},  {{ -4.299,  3.014, -2.904 }, { -3.154,  4.342, -2.683 }, { -3.000,  3.154, -4.129 }}}, // 60: 1.699, 1.809, 1.722: 5.2306m (~314 LEDs)
/*  61 */ { &strips[16*LEDS_PER_STRIP], {{ 314,  422}, { 423,  531}, { 532,  643}},  {{ -3.154,  4.342, -2.683 }, { -3.000,  3.154, -4.129 }, { -1.577,  4.342, -3.829 }}}, // 61: 1.809, 1.809, 1.881: 5.4995m (~330 LEDs)
/*  62 */ { &strips[16*LEDS_PER_STRIP], {{ 644,  752}, { 753,  854}, { 855,  957}},  {{ -3.000,  3.154, -4.129 }, { -1.577,  4.342, -3.829 }, { -1.433,  3.014, -4.986 }}}, // 62: 1.809, 1.699, 1.723: 5.2310m (~314 LEDs)
/*  63 */ { &strips[17*LEDS_PER_STRIP], {{   0,  101}, { 102,  204}, { 205,  306}},  {{ -1.577,  4.342, -3.829 }, { -1.433,  3.014, -4.986 }, { -0.000,  3.945, -4.521 }}}, // 63: 1.699, 1.703, 1.699: 5.1000m (~307 LEDs)
/*  64 */ { &strips[16*LEDS_PER_STRIP], {{ 958, 1060}, {1061, 1148}, {1149, 1234}},  {{ -1.433,  3.014, -4.986 }, { -0.000,  3.945, -4.521 }, { -0.000,  2.683, -5.367 }}}, // 64: 1.703, 1.451, 1.451: 4.6041m (~277 LEDs)
/*  65 */ { &strips[18*LEDS_PER_STRIP], {{   0,   87}, {  88,  190}, { 191,  276}},  {{  0.000,  2.683, -5.367 }, {  0.000,  3.945, -4.521 }, {  1.433,  3.014, -4.986 }}}, // 65: 1.451, 1.703, 1.451: 4.6041m (~277 LEDs)
/*  66 */ { &strips[17*LEDS_PER_STRIP], {{ 307,  409}, { 410,  511}, { 512,  613}},  {{  0.000,  3.945, -4.521 }, {  1.433,  3.014, -4.986 }, {  1.577,  4.342, -3.829 }}}, // 66: 1.703, 1.699, 1.699: 5.1000m (~307 LEDs)
/*  67 */ { &strips[18*LEDS_PER_STRIP], {{ 277,  378}, { 379,  487}, { 488,  590}},  {{  1.433,  3.014, -4.986 }, {  1.577,  4.342, -3.829 }, {  3.000,  3.154, -4.129 }}}, // 67: 1.699, 1.809, 1.723: 5.2310m (~314 LEDs)
/*  68 */ { &strips[18*LEDS_PER_STRIP], {{ 591,  699}, { 700,  808}, { 809,  920}},  {{  1.577,  4.342, -3.829 }, {  3.000,  3.154, -4.129 }, {  3.154,  4.342, -2.683 }}}, // 68: 1.809, 1.809, 1.881: 5.4995m (~330 LEDs)
/*  69 */ { &strips[18*LEDS_PER_STRIP], {{ 921, 1029}, {1030, 1131}, {1132, 1234}},  {{  3.000,  3.154, -4.129 }, {  3.154,  4.342, -2.683 }, {  4.299,  3.014, -2.904 }}}, // 69: 1.809, 1.699, 1.722: 5.2306m (~314 LEDs)
/*  70 */ { &strips[19*LEDS_PER_STRIP], {{   0,  101}, { 102,  204}, { 205,  306}},  {{  3.154,  4.342, -2.683 }, {  4.299,  3.014, -2.904 }, {  4.299,  3.945, -1.397 }}}, // 70: 1.699, 1.703, 1.699: 5.1003m (~307 LEDs)
/*  71 */ { &strips[19*LEDS_PER_STRIP], {{ 307,  409}, { 410,  497}, { 498,  583}},  {{  4.299,  3.014, -2.904 }, {  4.299,  3.945, -1.397 }, {  5.104,  2.683, -1.658 }}}, // 71: 1.703, 1.451, 1.451: 4.6053m (~277 LEDs)
/*  72 */ { &strips[20*LEDS_PER_STRIP], {{   0,   87}, {  88,  190}, { 191,  276}},  {{  5.104,  2.683, -1.658 }, {  4.299,  3.945, -1.397 }, {  5.185,  3.014, -0.178 }}}, // 72: 1.451, 1.703, 1.450: 4.6041m (~277 LEDs)
/*  73 */ { &strips[20*LEDS_PER_STRIP], {{ 277,  379}, { 380,  481}, { 482,  583}},  {{  4.299,  3.945, -1.397 }, {  5.185,  3.014, -0.178 }, {  4.129,  4.342,  0.317 }}}, // 73: 1.703, 1.699, 1.699: 5.1008m (~307 LEDs)
/*  74 */ { &strips[20*LEDS_PER_STRIP], {{ 584,  685}, { 686,  794}, { 795,  897}},  {{  5.185,  3.014, -0.178 }, {  4.129,  4.342,  0.317 }, {  4.854,  3.154,  1.577 }}}, // 74: 1.699, 1.809, 1.723: 5.2307m (~314 LEDs)
/*  75 */ { &strips[20*LEDS_PER_STRIP], {{ 898, 1006}, {1007, 1115}, {1116, 1227}},  {{  4.129,  4.342,  0.317 }, {  4.854,  3.154,  1.577 }, {  3.527,  4.342,  2.171 }}}, // 75: 1.809, 1.809, 1.881: 5.4987m (~330 LEDs)
/*  76 */ { &strips[21*LEDS_PER_STRIP], {{   0,  108}, { 109,  210}, { 211,  313}},  {{  4.854,  3.154,  1.577 }, {  3.527,  4.342,  2.171 }, {  4.090,  3.014,  3.192 }}}, // 76: 1.809, 1.699, 1.724: 5.2313m (~314 LEDs)
/*  77 */ { &strips[21*LEDS_PER_STRIP], {{ 314,  415}, { 416,  518}, { 519,  619}},  {{  3.527,  4.342,  2.171 }, {  4.090,  3.014,  3.192 }, {  2.657,  3.945,  3.657 }}}, // 77: 1.699, 1.703, 1.699: 5.0998m (~306 LEDs)
// row 3
/*  78 */ { &strips[13*LEDS_PER_STRIP], {{ 620,  721}, { 722,  825}, { 826,  933}},  {{ -0.975,  4.342,  4.025 }, { -2.657,  3.945,  3.657 }, { -1.854,  5.104,  2.552 }}}, // 78: 1.698, 1.723, 1.808: 5.2298m (~314 LEDs)
/*  79 */ { &strips[13*LEDS_PER_STRIP], {{ 934, 1037}, {1038, 1146}, {1147, 1247}},  {{ -2.657,  3.945,  3.657 }, { -1.854,  5.104,  2.552 }, { -3.527,  4.342,  2.171 }}}, // 79: 1.723, 1.809, 1.699: 5.2304m (~314 LEDs)
/*  80 */ { &strips[22*LEDS_PER_STRIP], {{   0,  108}, { 109,  221}, { 222,  329}},  {{ -1.854,  5.104,  2.552 }, { -3.527,  4.342,  2.171 }, { -2.552,  5.367,  0.829 }}}, // 80: 1.809, 1.881, 1.809: 5.4994m (~330 LEDs)
/*  81 */ { &strips[22*LEDS_PER_STRIP], {{ 330,  442}, { 443,  555}, { 556,  668}},  {{ -3.527,  4.342,  2.171 }, { -2.552,  5.367,  0.829 }, { -4.129,  4.342,  0.317 }}}, // 81: 1.881, 1.881, 1.881: 5.6430m (~339 LEDs)
/*  82 */ { &strips[22*LEDS_PER_STRIP], {{ 669,  781}, { 782,  890}, { 891,  998}},  {{ -2.552,  5.367,  0.829 }, { -4.129,  4.342,  0.317 }, { -3.000,  5.104, -0.975 }}}, // 82: 1.881, 1.809, 1.809: 5.4985m (~330 LEDs)
/*  83 */ { &strips[15*LEDS_PER_STRIP], {{ 584,  692}, { 693,  796}, { 797,  897}},  {{ -4.129,  4.342,  0.317 }, { -3.000,  5.104, -0.975 }, { -4.299,  3.945, -1.397 }}}, // 83: 1.809, 1.723, 1.699: 5.2308m (~314 LEDs)
/*  84 */ { &strips[15*LEDS_PER_STRIP], {{ 898, 1001}, {1002, 1110}, {1111, 1211}},  {{ -4.299,  3.945, -1.397 }, { -3.000,  5.104, -0.975 }, { -3.154,  4.342, -2.683 }}}, // 84: 1.723, 1.808, 1.699: 5.2294m (~314 LEDs)
/*  85 */ { &strips[23*LEDS_PER_STRIP], {{   0,  108}, { 109,  221}, { 222,  329}},  {{ -3.000,  5.104, -0.975 }, { -3.154,  4.342, -2.683 }, { -1.577,  5.367, -2.171 }}}, // 85: 1.808, 1.881, 1.809: 5.4977m (~330 LEDs)
/*  86 */ { &strips[23*LEDS_PER_STRIP], {{ 330,  442}, { 443,  555}, { 556,  668}},  {{ -3.154,  4.342, -2.683 }, { -1.577,  5.367, -2.171 }, { -1.577,  4.342, -3.829 }}}, // 86: 1.881, 1.881, 1.881: 5.6425m (~339 LEDs)
/*  87 */ { &strips[23*LEDS_PER_STRIP], {{ 669,  781}, { 782,  890}, { 891,  998}},  {{ -1.577,  5.367, -2.171 }, { -1.577,  4.342, -3.829 }, { -0.000,  5.104, -3.154 }}}, // 87: 1.881, 1.809, 1.808: 5.4976m (~330 LEDs)
/*  88 */ { &strips[17*LEDS_PER_STRIP], {{ 614,  722}, { 723,  826}, { 827,  927}},  {{ -1.577,  4.342, -3.829 }, { -0.000,  5.104, -3.154 }, { -0.000,  3.945, -4.521 }}}, // 88: 1.809, 1.724, 1.699: 5.2310m (~314 LEDs)
/*  89 */ { &strips[17*LEDS_PER_STRIP], {{ 928, 1031}, {1032, 1140}, {1141, 1241}},  {{  0.000,  3.945, -4.521 }, {  0.000,  5.104, -3.154 }, {  1.577,  4.342, -3.829 }}}, // 89: 1.724, 1.809, 1.699: 5.2310m (~314 LEDs)
/*  90 */ { &strips[24*LEDS_PER_STRIP], {{   0,  108}, { 109,  221}, { 222,  329}},  {{  0.000,  5.104, -3.154 }, {  1.577,  4.342, -3.829 }, {  1.577,  5.367, -2.171 }}}, // 90: 1.809, 1.881, 1.808: 5.4976m (~330 LEDs)
/*  91 */ { &strips[24*LEDS_PER_STRIP], {{ 330,  442}, { 443,  555}, { 556,  668}},  {{  1.577,  4.342, -3.829 }, {  1.577,  5.367, -2.171 }, {  3.154,  4.342, -2.683 }}}, // 91: 1.881, 1.881, 1.881: 5.6425m (~339 LEDs)
/*  92 */ { &strips[24*LEDS_PER_STRIP], {{ 669,  781}, { 782,  890}, { 891,  998}},  {{  1.577,  5.367, -2.171 }, {  3.154,  4.342, -2.683 }, {  3.000,  5.104, -0.975 }}}, // 92: 1.881, 1.808, 1.809: 5.4977m (~330 LEDs)
/*  93 */ { &strips[19*LEDS_PER_STRIP], {{ 584,  692}, { 693,  796}, { 797,  897}},  {{  3.154,  4.342, -2.683 }, {  3.000,  5.104, -0.975 }, {  4.299,  3.945, -1.397 }}}, // 93: 1.808, 1.723, 1.699: 5.2294m (~314 LEDs)
/*  94 */ { &strips[19*LEDS_PER_STRIP], {{ 898, 1001}, {1002, 1110}, {1111, 1211}},  {{  4.299,  3.945, -1.397 }, {  3.000,  5.104, -0.975 }, {  4.129,  4.342,  0.317 }}}, // 94: 1.723, 1.809, 1.699: 5.2308m (~314 LEDs)
/*  95 */ { &strips[25*LEDS_PER_STRIP], {{   0,  108}, { 109,  221}, { 222,  329}},  {{  3.000,  5.104, -0.975 }, {  4.129,  4.342,  0.317 }, {  2.552,  5.367,  0.829 }}}, // 95: 1.809, 1.881, 1.809: 5.4985m (~330 LEDs)
/*  96 */ { &strips[25*LEDS_PER_STRIP], {{ 330,  442}, { 443,  555}, { 556,  668}},  {{  4.129,  4.342,  0.317 }, {  2.552,  5.367,  0.829 }, {  3.527,  4.342,  2.171 }}}, // 96: 1.881, 1.881, 1.881: 5.6430m (~339 LEDs)
/*  97 */ { &strips[25*LEDS_PER_STRIP], {{ 669,  781}, { 782,  890}, { 891,  998}},  {{  2.552,  5.367,  0.829 }, {  3.527,  4.342,  2.171 }, {  1.854,  5.104,  2.552 }}}, // 97: 1.881, 1.809, 1.809: 5.4994m (~330 LEDs)
/*  98 */ { &strips[21*LEDS_PER_STRIP], {{ 620,  728}, { 729,  832}, { 833,  933}},  {{  3.527,  4.342,  2.171 }, {  1.854,  5.104,  2.552 }, {  2.657,  3.945,  3.657 }}}, // 98: 1.809, 1.723, 1.699: 5.2304m (~314 LEDs)
/*  99 */ { &strips[21*LEDS_PER_STRIP], {{ 934, 1037}, {1038, 1139}, {1140, 1247}},  {{  1.854,  5.104,  2.552 }, {  2.657,  3.945,  3.657 }, {  0.975,  4.342,  4.025 }}}, // 99: 1.723, 1.698, 1.808: 5.2298m (~314 LEDs)
/* 100 */ { &strips[26*LEDS_PER_STRIP], {{   0,  108}, { 109,  221}, { 222,  329}},  {{  1.854,  5.104,  2.552 }, {  0.975,  4.342,  4.025 }, { -0.000,  5.367,  2.683 }}}, // 100: 1.808, 1.881, 1.809: 5.4985m (~330 LEDs)
/* 101 */ { &strips[26*LEDS_PER_STRIP], {{ 330,  442}, { 443,  555}, { 556,  668}},  {{  0.975,  4.342,  4.025 }, { -0.000,  5.367,  2.683 }, { -0.975,  4.342,  4.025 }}}, // 101: 1.881, 1.881, 1.881: 5.6444m (~339 LEDs)
/* 102 */ { &strips[26*LEDS_PER_STRIP], {{ 669,  781}, { 782,  890}, { 891,  998}},  {{ -0.000,  5.367,  2.683 }, { -0.975,  4.342,  4.025 }, { -1.854,  5.104,  2.552 }}}, // 102: 1.881, 1.808, 1.809: 5.4985m (~330 LEDs)
// row 4
/* 103 */ { &strips[27*LEDS_PER_STRIP], {{   0,  108}, { 109,  212}, { 213,  313}},  {{ -0.000,  5.367,  2.683 }, { -1.854,  5.104,  2.552 }, { -0.886,  5.808,  1.219 }}}, // 103: 1.809, 1.723, 1.699: 5.2303m (~314 LEDs)
/* 104 */ { &strips[27*LEDS_PER_STRIP], {{ 314,  417}, { 418,  519}, { 520,  627}},  {{ -1.854,  5.104,  2.552 }, { -0.886,  5.808,  1.219 }, { -2.552,  5.367,  0.829 }}}, // 104: 1.723, 1.698, 1.809: 5.2305m (~314 LEDs)
/* 105 */ { &strips[28*LEDS_PER_STRIP], {{   0,  101}, { 102,  203}, { 204,  306}},  {{ -0.886,  5.808,  1.219 }, { -2.552,  5.367,  0.829 }, { -1.433,  5.808, -0.466 }}}, // 105: 1.698, 1.699, 1.703: 5.1004m (~307 LEDs)
/* 106 */ { &strips[28*LEDS_PER_STRIP], {{ 307,  408}, { 409,  512}, { 513,  620}},  {{ -2.552,  5.367,  0.829 }, { -1.433,  5.808, -0.466 }, { -3.000,  5.104, -0.975 }}}, // 106: 1.699, 1.723, 1.809: 5.2309m (~314 LEDs)
/* 107 */ { &strips[28*LEDS_PER_STRIP], {{ 621,  724}, { 725,  826}, { 827,  934}},  {{ -3.000,  5.104, -0.975 }, { -1.433,  5.808, -0.466 }, { -1.577,  5.367, -2.171 }}}, // 107: 1.723, 1.698, 1.809: 5.2306m (~314 LEDs)
/* 108 */ { &strips[29*LEDS_PER_STRIP], {{   0,  101}, { 102,  203}, { 204,  305}},  {{ -1.433,  5.808, -0.466 }, { -1.577,  5.367, -2.171 }, { -0.000,  5.808, -1.507 }}}, // 108: 1.698, 1.699, 1.703: 5.0997m (~306 LEDs)
/* 109 */ { &strips[29*LEDS_PER_STRIP], {{ 306,  407}, { 408,  511}, { 512,  619}},  {{ -1.577,  5.367, -2.171 }, { -0.000,  5.808, -1.507 }, { -0.000,  5.104, -3.154 }}}, // 109: 1.699, 1.723, 1.808: 5.2295m (~314 LEDs)
/* 110 */ { &strips[29*LEDS_PER_STRIP], {{ 620,  723}, { 724,  825}, { 826,  933}},  {{  0.000,  5.104, -3.154 }, {  0.000,  5.808, -1.507 }, {  1.577,  5.367, -2.171 }}}, // 110: 1.723, 1.699, 1.808: 5.2295m (~314 LEDs)
/* 111 */ { &strips[30*LEDS_PER_STRIP], {{   0,  101}, { 102,  203}, { 204,  305}},  {{  0.000,  5.808, -1.507 }, {  1.577,  5.367, -2.171 }, {  1.433,  5.808, -0.466 }}}, // 111: 1.699, 1.698, 1.703: 5.0997m (~306 LEDs)
/* 112 */ { &strips[30*LEDS_PER_STRIP], {{ 306,  407}, { 408,  511}, { 512,  619}},  {{  1.577,  5.367, -2.171 }, {  1.433,  5.808, -0.466 }, {  3.000,  5.104, -0.975 }}}, // 112: 1.698, 1.723, 1.809: 5.2306m (~314 LEDs)
/* 113 */ { &strips[30*LEDS_PER_STRIP], {{ 620,  723}, { 724,  825}, { 826,  933}},  {{  3.000,  5.104, -0.975 }, {  1.433,  5.808, -0.466 }, {  2.552,  5.367,  0.829 }}}, // 113: 1.723, 1.699, 1.809: 5.2309m (~314 LEDs)
/* 114 */ { &strips[31*LEDS_PER_STRIP], {{   0,  101}, { 102,  203}, { 204,  306}},  {{  1.433,  5.808, -0.466 }, {  2.552,  5.367,  0.829 }, {  0.886,  5.808,  1.219 }}}, // 114: 1.699, 1.698, 1.703: 5.1004m (~307 LEDs)
/* 115 */ { &strips[31*LEDS_PER_STRIP], {{ 307,  408}, { 409,  512}, { 513,  620}},  {{  2.552,  5.367,  0.829 }, {  0.886,  5.808,  1.219 }, {  1.854,  5.104,  2.552 }}}, // 115: 1.698, 1.723, 1.809: 5.2305m (~314 LEDs)
/* 116 */ { &strips[31*LEDS_PER_STRIP], {{ 621,  724}, { 725,  826}, { 827,  934}},  {{  1.854,  5.104,  2.552 }, {  0.886,  5.808,  1.219 }, { -0.000,  5.367,  2.683 }}}, // 116: 1.723, 1.699, 1.809: 5.2303m (~314 LEDs)
/* 117 */ { &strips[27*LEDS_PER_STRIP], {{ 628,  729}, { 730,  831}, { 832,  934}},  {{  0.886,  5.808,  1.219 }, { -0.000,  5.367,  2.683 }, { -0.886,  5.808,  1.219 }}}, // 117: 1.699, 1.699, 1.704: 5.1008m (~307 LEDs)
// row 5
/* 118 */ { &strips[27*LEDS_PER_STRIP], {{ 935, 1037}, {1038, 1125}, {1126, 1211}},  {{  0.886,  5.808,  1.219 }, { -0.886,  5.808,  1.219 }, { -0.000,  6.000,  0.000 }}}, // 118: 1.704, 1.451, 1.451: 4.6048m (~277 LEDs)
/* 119 */ { &strips[28*LEDS_PER_STRIP], {{ 935, 1022}, {1023, 1110}, {1111, 1211}},  {{ -0.886,  5.808,  1.219 }, { -0.000,  6.000,  0.000 }, { -1.433,  5.808, -0.466 }}}, // 119: 1.451, 1.451, 1.703: 4.6043m (~277 LEDs)
/* 120 */ { &strips[29*LEDS_PER_STRIP], {{ 934, 1036}, {1037, 1124}, {1125, 1210}},  {{ -1.433,  5.808, -0.466 }, { -0.000,  5.808, -1.507 }, { -0.000,  6.000,  0.000 }}}, // 120: 1.703, 1.451, 1.451: 4.6039m (~277 LEDs)
/* 121 */ { &strips[30*LEDS_PER_STRIP], {{ 934, 1021}, {1022, 1109}, {1110, 1210}},  {{ -0.000,  5.808, -1.507 }, { -0.000,  6.000,  0.000 }, {  1.433,  5.808, -0.466 }}}, // 121: 1.451, 1.451, 1.703: 4.6039m (~277 LEDs)
/* 122 */ { &strips[31*LEDS_PER_STRIP], {{ 935, 1022}, {1023, 1125}, {1126, 1211}},  {{ -0.000,  6.000,  0.000 }, {  1.433,  5.808, -0.466 }, {  0.886,  5.808,  1.219 }}}, // 122: 1.451, 1.703, 1.451: 4.6043m (~277 LEDs)
};
// TOTAL LEDS: 38333
