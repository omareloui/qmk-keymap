#pragma once

#define CHORDAL_HOLD

#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM_PER_KEY

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// Define speed curve for Orbital Mouse.
#define ORBITAL_MOUSE_SPEED_CURVE {24, 24, 24, 32, 62, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72}
//                                 |               |               |               |           |
//                             t = 0.000           1.024           2.048           3.072       3.840 s
