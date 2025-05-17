#include "process_tap_dance.h"
#include "quantum.h"

enum {
    TD_LABK,
    TD_LBRC,
    TD_LCBR,
    TD_LPRN,
    TD_RABK,
    TD_RBRC,
    TD_RCBR,
    TD_RPRN,
    TD_SCLN,
    TD_COLN,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

#define SYM_LABK TD(TD_LABK)
#define SYM_LBRC TD(TD_LBRC)
#define SYM_LCBR TD(TD_LCBR)
#define SYM_LPRN TD(TD_LPRN)
#define SYM_RABK TD(TD_RABK)
#define SYM_RBRC TD(TD_RBRC)
#define SYM_RCBR TD(TD_RCBR)
#define SYM_RPRN TD(TD_RPRN)
#define SYM_SCLN TD(TD_SCLN)
#define SYM_COLN TD(TD_COLN)

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                        \
    {                                                                               \
        .fn        = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),               \
    }

#define ACTION_TAP_DANCE_PREPEND_END_ON_HOLD(keycode)                                                   \
    {                                                                                                   \
        .fn        = {NULL, tap_dance_tap_hold_prepend_end_on_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){keycode, 0, 0}),                                  \
    }

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_prepend_end_on_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1 && !state->interrupted) {
            tap_code(KC_END);
        }

        register_code16(tap_hold->tap);
        tap_hold->held = tap_hold->tap;
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}
