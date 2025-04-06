#pragma once

#define CHORDAL_HOLD

#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM_PER_KEY

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// Don't apply custom shift keys with mods other than Shift.
#define CUSTOM_SHIFT_KEYS_NEGMODS ~MOD_MASK_SHIFT

// Only apply custom shift keys on layers 0, 1 and 5.
#define CUSTOM_SHIFT_KEYS_LAYER_MASK (1 << 0) | (1 << 1) | (1 << 5)

// When idle, turn off Layer Lock after 60 seconds.
#define LAYER_LOCK_IDLE_TIMEOUT 60000

// When idle, turn off Sentence Case after 2 seconds.
#define SENTENCE_CASE_TIMEOUT 2000

// Define speed curve for Orbital Mouse.
// clang-format off
#define ORBITAL_MOUSE_SPEED_CURVE \
      {10, 11, 16, 23, 34, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42}
//     |               |               |               |           |
// t = 0.000           1.024           2.048           3.072       3.840 s
// clang-format on

// Enable all effects and palettes in PaletteFx.
#define PALETTEFX_ENABLE_ALL_EFFECTS
#define PALETTEFX_ENABLE_ALL_PALETTES
