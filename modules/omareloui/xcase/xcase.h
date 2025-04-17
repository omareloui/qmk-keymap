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

#pragma once

#include QMK_KEYBOARD_H

// enum for the xcase states
enum xcase_state {
    XCASE_OFF = 0, // xcase is off
    XCASE_ON,      // xcase is actively on
    XCASE_WAIT,    // xcase is waiting for the delimiter input
};

// Get xcase state
enum xcase_state get_xcase_state(void);

void set_xcase_state(enum xcase_state state, uint16_t delimiter);
void enable_xcase(void);
void enable_xcase_with(uint16_t delimiter);
void disable_xcase(void);

// Optional callback to indicate primed state.
void xcase_primed(bool primed);

bool process_case_modes(uint16_t keycode, const keyrecord_t *record);
