#pragma once

#include QMK_KEYBOARD_H

typedef struct {
    uint16_t delimiter;
    bool     capture_first : 1;
    bool     with_space : 1;
} xcase_config_t;

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
void xcase_set_user(bool active);
