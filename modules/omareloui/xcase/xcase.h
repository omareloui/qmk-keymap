/* Copyright 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae
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
typedef enum xcase_state { XCASE_OFF, XCASE_WAIT, XCASE_ON } xcase_state_t;

typedef struct {
    uint16_t delimiter;
    bool     capture_first : 1;
    bool     with_space : 1;
} xcase_config_t;

// Get xcase state
xcase_state_t get_xcase_state(void);
// Enable xcase and pickup the next keystroke as the delimiter
void enable_xcase(void);
// Enable xcase with the specified delimiter
void enable_xcase_with(xcase_config_t config);
// Disable xcase
void disable_xcase(void);

// Function to be put in process user
bool process_case_modes(uint16_t keycode, const keyrecord_t *record);

// Helper funcions
void enable_title_case(void);
void enable_snake_case(void);
void enable_kebab_case(void);
void enable_camel_case(void);
void enable_pascal_case(void);
void enable_path_case(void);

bool terminate_case_modes_user(uint16_t keycode, const keyrecord_t *record);
bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record);
