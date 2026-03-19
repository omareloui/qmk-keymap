#pragma once

#include "quantum.h"

__attribute__((weak)) bool terminate_case_modes_user(uint16_t keycode, const keyrecord_t *record) {
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
                clear_oneshot_mods();
                return true;
            }
            break;
    }
    return false;
}

__attribute__((weak)) void xcase_set_user(bool active) {}
