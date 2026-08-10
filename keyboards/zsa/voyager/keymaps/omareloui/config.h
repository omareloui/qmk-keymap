#pragma once

#define CHORDAL_HOLD

#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM_PER_KEY
#define SPECULATIVE_HOLD

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_LINUX

// Don't apply custom shift keys with mods other than Shift.
#define CUSTOM_SHIFT_KEYS_NEGMODS ~MOD_MASK_SHIFT

// Only apply custom shift keys on STRDY, SYM and EXT (0, 2 and 8).
#define CUSTOM_SHIFT_KEYS_LAYER_MASK (1 << 0) | (1 << 2) | (1 << 8)

// When idle, turn off Layer Lock after 60 seconds.
#define LAYER_LOCK_IDLE_TIMEOUT 60000

// When idle, turn off Sentence Case after 2 seconds.
#define SENTENCE_CASE_TIMEOUT 2000

// Define speed curve for Orbital Mouse.
// clang-format off
#define ORBITAL_MOUSE_SPEED_CURVE \
      {24, 24, 24, 32, 62, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72}
//     |               |               |               |           |
// t = 0.000           1.024           2.048           3.072       3.840 s
// clang-format on

// Enable all effects and palettes in PaletteFx.
#define PALETTEFX_ENABLE_ALL_EFFECTS
#define PALETTEFX_ENABLE_ALL_PALETTES

#ifdef COMMUNITY_MODULE_PALETTEFX_ENABLE
// Since we have PaletteFx, disable most built-in RGB Matrix effects.
#    undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#    undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_BREATHING
#    undef ENABLE_RGB_MATRIX_BAND_SAT
#    undef ENABLE_RGB_MATRIX_BAND_VAL
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    undef ENABLE_RGB_MATRIX_CYCLE_ALL
#    undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    undef ENABLE_RGB_MATRIX_DUAL_BEACON
#    undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    undef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#    undef ENABLE_RGB_MATRIX_RAINDROPS
#    undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    undef ENABLE_RGB_MATRIX_HUE_BREATHING
#    undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#    undef ENABLE_RGB_MATRIX_HUE_WAVE
#    undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#    undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#    undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#    undef ENABLE_RGB_MATRIX_STARLIGHT
#    undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#    undef ENABLE_RGB_MATRIX_RIVERFLOW
#    undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    undef ENABLE_RGB_MATRIX_SPLASH
#    undef ENABLE_RGB_MATRIX_MULTISPLASH
#    undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#    undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif // COMMUNITY_MODULE_PALETTEFX_ENABLE

// Auto-switch to the NAVIGATOR layer on trackball motion, back to base once it's
// idle. Must match NAVIGATOR's position in `enum layers` in keymap.c (config.h
// can't see that enum, it lives in a different translation unit).
#define AUTOMOUSE_LAYER 2
#define AUTOMOUSE_ENABLED_TRACKPAD false // No trackpad on this build, only the trackball.
#define AUTOMOUSE_TIMEOUT_TRACKBALL 5000 // ms idle before dropping back to base (default 650).

#define DYNAMIC_MACRO_NO_NESTING

#define ENABLE_MOUSE_JIGGLER

#define CYCLOTAB_TIMEOUT 0
