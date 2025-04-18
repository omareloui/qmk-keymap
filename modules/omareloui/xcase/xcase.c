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

#define IS_OSM(keycode) (keycode >= QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX)

// State variables with bitfields for optimization
static struct {
    xcase_state_t state : 2;
    bool          at_start : 1;
    bool          with_space : 1;
    int16_t       dist_to_delim;
    uint8_t       delim_count;
    uint16_t      delimiter;
} xcase = {.state = XCASE_OFF, .at_start = false, .with_space = false, .delim_count = 0, .delimiter = 0};

// Get xcase state
enum xcase_state get_xcase_state(void) {
    return xcase.state;
}

// Place the current xcase delimiter
static void place_delimiter(void) {
    if (IS_OSM(xcase.delimiter)) {
        set_oneshot_mods(xcase.delimiter - QK_ONE_SHOT_MOD);
    } else {
        tap_code16(xcase.delimiter);
    }
    xcase.at_start = false;
}

// Enable xcase and pickup the next keystroke as the delimiter
void enable_xcase(void) {
    xcase.state = XCASE_WAIT;
}

// Enable xcase with the specified delimiter
void enable_xcase_with(xcase_config_t config) {
    xcase.state         = XCASE_ON;
    xcase.delimiter     = config.delimiter;
    xcase.dist_to_delim = -1;
    xcase.delim_count   = 0;
    xcase.with_space    = config.with_space;
    xcase.at_start      = true;

    if (config.capture_first) {
        xcase.delim_count++;
        place_delimiter();
        xcase.dist_to_delim++;
    }
}

// Disable xcase
void disable_xcase(void) {
    xcase.state = XCASE_OFF;
}

// Removes a delimiter, used for double tap space exit

static void remove_delimiter(void) {
    bool is_mod = IS_OSM(xcase.delimiter);

    if (is_mod) {
        clear_oneshot_mods();
    }

    if (!is_mod || (!xcase.at_start && xcase.with_space)) {
        for (int8_t i = 0; i < DEFAULT_DELIMITERS_TERMINATE_COUNT - 1; i++) {
            tap_code16(KC_BSPC);
        }
    }
}

bool process_case_modes(uint16_t keycode, const keyrecord_t *record) {
    if (!xcase.state) {
        return true;
    }

    if ((QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX) || (QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX)) {
        // Earlier return if this has not been considered tapped yet
        if (record->tap.count == 0) return true;
        keycode = keycode & 0xFF;
    }

    if (keycode >= QK_LAYER_TAP && keycode <= QK_ONE_SHOT_LAYER_MAX) {
        // let special keys and normal modifiers go through
        return true;
    }

    if (xcase.state == XCASE_WAIT) {
        // grab the next input to be the delimiter
        if (use_default_xcase_separator(keycode, record)) {
            enable_xcase_with((xcase_config_t){.delimiter = DEFAULT_XCASE_SEPARATOR});
        } else if (record->event.pressed) {
            // factor in mods
            if (get_mods() & MOD_MASK_SHIFT) {
                keycode = LSFT(keycode);
            } else if (get_mods() & MOD_BIT(KC_RALT)) {
                keycode = RALT(keycode);
            }
            enable_xcase_with((xcase_config_t){.delimiter = keycode});
            return false;
        } else {
            if (IS_OSM(keycode)) {
                // this catches the OSM release if no other key was pressed
                set_oneshot_mods(0);
                enable_xcase_with((xcase_config_t){.delimiter = keycode});
                return false;
            }
            // let other special keys go through
            return true;
        }
    }

    if (!record->event.pressed || xcase.state != XCASE_ON) {
        return true;
    }

    if (keycode == KC_SPACE) {
        xcase.delim_count++;
        if (xcase.delim_count < DEFAULT_DELIMITERS_TERMINATE_COUNT) {
            if (!xcase.at_start && xcase.with_space) {
                tap_code16(KC_SPACE);
            }
            place_delimiter();
            xcase.dist_to_delim = 0;
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
        --xcase.dist_to_delim;
        if (xcase.delim_count > 0) {
            --xcase.delim_count;
        }
    }
    // don't increment distance to last delim if negative
    else if (xcase.dist_to_delim >= 0) {
        // puts back a one shot delimiter if you we're back to the delimiter pos
        if (xcase.dist_to_delim == 0 && IS_OSM(xcase.delimiter)) {
            place_delimiter();
        }
        ++xcase.dist_to_delim;
        xcase.delim_count = 0;
    }

    // check if the case modes have been terminated
    if (terminate_case_modes(keycode, record)) {
        disable_xcase();
    }

    return true;
}

void enable_title_case(void) {
    enable_xcase_with((xcase_config_t){.delimiter = OSM(MOD_LSFT), .capture_first = true, .with_space = true});
}

void enable_snake_case(void) {
    enable_xcase_with((xcase_config_t){.delimiter = KC_UNDS, .capture_first = false, .with_space = false});
}

void enable_kebab_case(void) {
    enable_xcase_with((xcase_config_t){.delimiter = KC_MINUS, .capture_first = false, .with_space = false});
}

void enable_camel_case(void) {
    enable_xcase_with((xcase_config_t){.delimiter = OSM(MOD_LSFT), .capture_first = false, .with_space = false});
}

void enable_pascal_case(void) {
    enable_xcase_with((xcase_config_t){.delimiter = OSM(MOD_LSFT), .capture_first = true, .with_space = false});
}

void enable_path_case(void) {
    enable_xcase_with((xcase_config_t){.delimiter = KC_SLSH, .capture_first = false, .with_space = false});
}

bool process_record_xcase(uint16_t keycode, keyrecord_t *record) {
    // Process case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case XC_TITLECASE:
            enable_title_case();
            return false;
        case XC_SNAKECASE:
            enable_snake_case();
            return false;
        case XC_PASCALCASE:
            enable_pascal_case();
            return false;
        case XC_CAMELCASE:
            enable_camel_case();
            return false;
        case XC_KEBABCASE:
            enable_kebab_case();
            return false;
        case XC_PATHCASE:
            enable_path_case();
            return false;
        default:
            return true;
    }
}
