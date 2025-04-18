/* Copyright 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae
 * Copyright 2025 Omar Eloui contact@omareloui.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "xcase.h"

#ifndef DEFAULT_XCASE_SEPARATOR
#    define DEFAULT_XCASE_SEPARATOR KC_UNDS
#endif

#ifndef DEFAULT_DELIMITERS_TERMINATE_COUNT
#    define DEFAULT_DELIMITERS_TERMINATE_COUNT 2
#endif

#define IS_OSM(keycode) (keycode >= KC_LEFT_CTRL && keycode <= KC_RIGHT_GUI)

// enum to keep track of the xcase state
static enum xcase_state xcase_state = XCASE_OFF;
// the keycode of the xcase delimiter
static uint16_t xcase_delimiter;
// the number of keys to the last delimiter
static int8_t distance_to_last_delim = -1;
// the number of delimiters in a row
static int8_t delimiters_count = 0;

// Get xcase state
enum xcase_state get_xcase_state(void) {
    return xcase_state;
}

// Place the current xcase delimiter
static void place_delimiter(void) {
    if (IS_OSM(xcase_delimiter)) {
        set_oneshot_mods(MOD_BIT(xcase_delimiter));
    } else {
        tap_code16(xcase_delimiter);
    }
}

// Enable xcase and pickup the next keystroke as the delimiter
void enable_xcase(void) {
    xcase_state = XCASE_WAIT;
}

// Enable xcase with the specified delimiter
void enable_xcase_with(uint16_t delimiter, bool capture) {
    xcase_state            = XCASE_ON;
    xcase_delimiter        = delimiter;
    distance_to_last_delim = -1;
    delimiters_count       = 0;
    if (capture) {
        delimiters_count++;
        place_delimiter();
        distance_to_last_delim = 0;
    }
}

// Disable xcase
void disable_xcase(void) {
    xcase_state = XCASE_OFF;
}

// Removes a delimiter, used for double tap space exit
static void remove_delimiter(void) {
    if (IS_OSM(xcase_delimiter)) {
        clear_oneshot_mods();
    } else {
        for (int8_t i = 0; i < DEFAULT_DELIMITERS_TERMINATE_COUNT - 1; i++) {
            tap_code(KC_BSPC);
        }
    }
}

// overrideable function to determine whether the case mode should stop
__attribute__((weak)) bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                return true;
            }
            break;
        default:
            if (record->event.pressed) {
                return true;
            }
            break;
    }
    return false;
}

/* overrideable function to determine whether to use the default separator on
 * first keypress when waiting for the separator. */
__attribute__((weak)) bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record) {
    // for example:
    /* switch (keycode) { */
    /*     case KC_A ... KC_Z: */
    /*     case KC_1 ... KC_0: */
    /*         return true; */
    /* } */
    return false;
}

bool process_case_modes(uint16_t keycode, const keyrecord_t *record) {
    if (xcase_state) {
        if ((QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX) || (QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX)) {
            // Earlier return if this has not been considered tapped yet
            if (record->tap.count == 0) return true;
            keycode = keycode & 0xFF;
        }

        if (keycode >= QK_LAYER_TAP && keycode <= QK_ONE_SHOT_LAYER_MAX) {
            // let special keys and normal modifiers go through
            return true;
        }

        if (xcase_state == XCASE_WAIT) {
            // grab the next input to be the delimiter
            if (use_default_xcase_separator(keycode, record)) {
                enable_xcase_with(DEFAULT_XCASE_SEPARATOR, false);
            } else if (record->event.pressed) {
                // factor in mods
                if (get_mods() & MOD_MASK_SHIFT) {
                    keycode = LSFT(keycode);
                } else if (get_mods() & MOD_BIT(KC_RALT)) {
                    keycode = RALT(keycode);
                }
                enable_xcase_with(keycode, false);
                return false;
            } else {
                if (IS_OSM(keycode)) {
                    // this catches the OSM release if no other key was pressed
                    set_oneshot_mods(0);
                    enable_xcase_with(keycode, false);
                    return false;
                }
                // let other special keys go through
                return true;
            }
        }

        if (record->event.pressed) {
            // handle xcase mode
            if (xcase_state == XCASE_ON) {
                // place the delimiter if space is tapped
                if (keycode == KC_SPACE) {
                    delimiters_count++;
                    if (delimiters_count < DEFAULT_DELIMITERS_TERMINATE_COUNT) {
                        place_delimiter();
                        distance_to_last_delim = 0;
                        return false;
                    }

                    // remove the delimiter and disable modes
                    else {
                        remove_delimiter();
                        disable_xcase();
                        return true;
                    }
                }
                // decrement distance to delimiter on back space
                else if (keycode == KC_BSPC) {
                    --distance_to_last_delim;
                    if (delimiters_count > 0) {
                        --delimiters_count;
                    }
                }
                // don't increment distance to last delim if negative
                else if (distance_to_last_delim >= 0) {
                    // puts back a one shot delimiter if you we're back to the delimiter pos
                    if (distance_to_last_delim == 0 && (IS_OSM(xcase_delimiter))) {
                        place_delimiter();
                    }
                    ++distance_to_last_delim;
                    delimiters_count = 0;
                }

            } // end XCASE_ON

            // check if the case modes have been terminated
            if (terminate_case_modes(keycode, record)) {
                disable_xcase();
            }
        } // end if event.pressed

        return true;
    }
    return true;
}

bool process_record_xcase(uint16_t keycode, keyrecord_t *record) {
    // Process case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case XC_SNAKECASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_UNDS, false);
            }
            return false;
        case XC_PASCALCASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_LSFT, true);
            }
            return false;
        case XC_CAMELCASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_LSFT, false);
            }
            return false;
        case XC_KEBABCASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_MINS, false);
            }
            return false;
        case XC_PATHCASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_SLSH, false);
            }
            return false;
        default:
            return true;
    }
}
