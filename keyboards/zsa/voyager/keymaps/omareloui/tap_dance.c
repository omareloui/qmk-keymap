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
};

#define TAP_DANCE_FN_PREPPEND_END(keycode)                                              \
    static void _td_preppend_end_##keycode(tap_dance_state_t *state, void *user_data) { \
        if (state->count == 1) {                                                        \
            tap_code16(KC_##keycode);                                                   \
            reset_tap_dance(state);                                                     \
        } else if (state->count >= 2) {                                                 \
            tap_code16(KC_END);                                                         \
            tap_code16(KC_##keycode);                                                   \
            reset_tap_dance(state);                                                     \
        }                                                                               \
    }

#define TAP_DANCE_ENTRY_PREPPEND_END(keycode) [TD_##keycode] = ACTION_TAP_DANCE_FN(_td_preppend_end_##keycode)

#define SYM_LABK TD(TD_LABK)
#define SYM_LBRC TD(TD_LBRC)
#define SYM_LCBR TD(TD_LCBR)
#define SYM_LPRN TD(TD_LPRN)
#define SYM_RABK TD(TD_RABK)
#define SYM_RBRC TD(TD_RBRC)
#define SYM_RCBR TD(TD_RCBR)
#define SYM_RPRN TD(TD_RPRN)
#define SYM_SCLN TD(TD_SCLN)

TAP_DANCE_FN_PREPPEND_END(LABK);
TAP_DANCE_FN_PREPPEND_END(LBRC);
TAP_DANCE_FN_PREPPEND_END(LCBR);
TAP_DANCE_FN_PREPPEND_END(LPRN);
TAP_DANCE_FN_PREPPEND_END(RABK);
TAP_DANCE_FN_PREPPEND_END(RBRC);
TAP_DANCE_FN_PREPPEND_END(RCBR);
TAP_DANCE_FN_PREPPEND_END(RPRN);
TAP_DANCE_FN_PREPPEND_END(SCLN);

tap_dance_action_t tap_dance_actions[] = {
    TAP_DANCE_ENTRY_PREPPEND_END(LABK), TAP_DANCE_ENTRY_PREPPEND_END(RABK),

    TAP_DANCE_ENTRY_PREPPEND_END(LBRC), TAP_DANCE_ENTRY_PREPPEND_END(RBRC),

    TAP_DANCE_ENTRY_PREPPEND_END(LCBR), TAP_DANCE_ENTRY_PREPPEND_END(RCBR),

    TAP_DANCE_ENTRY_PREPPEND_END(LPRN), TAP_DANCE_ENTRY_PREPPEND_END(RPRN),

    TAP_DANCE_ENTRY_PREPPEND_END(SCLN),
};
