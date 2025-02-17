// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2025 Omar Eloui  (@omareloui) <contact@omareloui.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* #ifdef ACHORDION_ENABLE */
/* #    include "features/achordion.h" */
/* #endif // ACHORDION_ENABLE */
/* #ifdef CUSTOM_SHIFT_KEYS_ENABLE */
/* #    include "features/custom_shift_keys.h" */
/* #endif // CUSTOM_SHIFT_KEYS_ENABLE */
/* #ifdef KEYCODE_STRING_ENABLE */
/* #    include "features/keycode_string.h" */
/* #endif // KEYCODE_STRING_ENABLE */
/* #ifdef ORBITAL_MOUSE_ENABLE */
/* #    include "features/orbital_mouse.h" */
/* #endif // ORBITAL_MOUSE_ENABLE */
/* #ifdef RGB_MATRIX_CUSTOM_USER */
/* #    include "features/palettefx.h" */
/* #endif // RGB_MATRIX_CUSTOM_USER */
#ifdef SELECT_WORD_ENABLE
#    include "features/select_word.h"
#endif // SELECT_WORD_ENABLE
/* #ifdef SENTENCE_CASE_ENABLE */
/* #    include "features/sentence_case.h" */
/* #endif // SENTENCE_CASE_ENABLE */

enum layers {
    BASE,
    SYM,
    NAV,
    NUM,
    WIN,
    FUN,
    EXT,
};

enum custom_keycodes {
    USRNAME = SAFE_RANGE,
    SRCHSEL,
    ARROW,
    SELLINE,
    SELWBAK,
    SELWFWD,
};

#define HRM_DOT LT(WIN, KC_DOT)
#define HRM_F LT(NAV, KC_F)
#define HRM_J LT(NUM, KC_J)
#define HRM_K RSFT_T(KC_K)

#define NOTIMPLE KC_NO
#define MUTEMIC KC_F20

#ifdef CHORDAL_HOLD
// clang-format off
// Handedness for Chordal Hold (https://github.com/qmk/qmk_firmware/pull/24560)
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  '*', '*', '*', '*', '*', '*',              '*' , '*' , '*' , '*' , '*' , '*' ,
  '*', 'L', 'L', 'L', 'L', 'L',              'R' , 'R' , 'R' , 'R' , 'R' , '*' ,
  '*', 'L', 'L', 'L', 'L', 'L',              'R', 'R', 'R' , 'R' , 'R' , '*' ,
  '*', 'L', 'L', 'L', 'L', 'L',              'R', 'R' , 'R' , 'R' , 'R' , '*' ,
                           'L', 'L',    'R', 'R'
);
// clang-format on
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────┬───────────┬────────────┬───────────┬───────────┬──────────┐                  ┌──────┬────────────┬───────────┬────────────┬───────────┬──────┐
//    │    `    │  SELLINE  │    C(v)    │   C(a)    │   C(c)    │ NOTIMPLE │                  │ home │    left    │   rght    │    end     │  G(tab)   │ mply │
//    ├─────────┼───────────┼────────────┼───────────┼───────────┼──────────┤                  ├──────┼────────────┼───────────┼────────────┼───────────┼──────┤
//    │   tab   │     q     │     w      │     e     │     r     │    t     │                  │  y   │     u      │     i     │     o      │     p     │  /   │
//    ├─────────┼───────────┼────────────┼───────────┼───────────┼──────────┤                  ├──────┼────────────┼───────────┼────────────┼───────────┼──────┤
//    │  bspc   │ LALT_T(a) │ LT(SYM, s) │ LSFT_T(d) │   HRM_F   │    g     │                  │  h   │ LT(NUM, j) │ RSFT_T(k) │ LT(SYM, l) │ LALT_T(;) │  -   │
//    ├─────────┼───────────┼────────────┼───────────┼───────────┼──────────┤                  ├──────┼────────────┼───────────┼────────────┼───────────┼──────┤
//    │ MO(EXT) │ LGUI_T(z) │     x      │     c     │ LCTL_T(v) │    b     │                  │  n   │ RCTL_T(m)  │     ,     │  HRM_DOT   │ RGUI_T(/) │ ent  │
//    └─────────┴───────────┴────────────┴───────────┴───────────┼──────────┼─────┐   ┌────────┼──────┼────────────┴───────────┴────────────┴───────────┴──────┘
//                                                               │    _     │ spc │   │ QK_REP │ esc  │
//                                                               └──────────┴─────┘   └────────┴──────┘
[BASE] = LAYOUT(
  KC_GRV  , SELLINE      , C(KC_V)       , C(KC_A)      , C(KC_C)      , NOTIMPLE ,                       KC_HOME , KC_LEFT       , KC_RGHT      , KC_END        , G(KC_TAB)       , KC_MPLY,
  KC_TAB  , KC_Q         , KC_W          , KC_E         , KC_R         , KC_T     ,                       KC_Y    , KC_U          , KC_I         , KC_O          , KC_P            , KC_SLSH,
  KC_BSPC , LALT_T(KC_A) , LT(SYM, KC_S) , LSFT_T(KC_D) , HRM_F        , KC_G     ,                       KC_H    , LT(NUM, KC_J) , RSFT_T(KC_K) , LT(SYM, KC_L) , LALT_T(KC_SCLN) , KC_MINS,
  MO(EXT) , LGUI_T(KC_Z) , KC_X          , KC_C         , LCTL_T(KC_V) , KC_B     ,                       KC_N    , RCTL_T(KC_M)  , KC_COMMA     , HRM_DOT       , RGUI_T(KC_SLSH) , KC_ENT ,
                                                                         KC_UNDS  , KC_SPC ,     QK_REP , KC_ESC
),

//    ┌─────┬─────┬─────┬───────────┬─────────────┬─────────┐               ┌─────┬─────┬─────┬─────┬───────┬─────┐
//    │     │     │     │           │             │         │               │     │     │     │     │       │     │
//    ├─────┼─────┼─────┼───────────┼─────────────┼─────────┤               ├─────┼─────┼─────┼─────┼───────┼─────┤
//    │     │  `  │  <  │     >     │      -      │    |    │               │  ^  │  $  │  {  │  }  │ ARROW │     │
//    ├─────┼─────┼─────┼───────────┼─────────────┼─────────┤               ├─────┼─────┼─────┼─────┼───────┼─────┤
//    │     │  !  │  *  │ LSFT_T(/) │ LT(BASE, =) │    &    │               │  #  │  ;  │  (  │  )  │   "   │     │
//    ├─────┼─────┼─────┼───────────┼─────────────┼─────────┤               ├─────┼─────┼─────┼─────┼───────┼─────┤
//    │     │  ~  │  [  │     ]     │      +      │    %    │               │  @  │  :  │  ,  │  .  │   '   │     │
//    └─────┴─────┴─────┴───────────┴─────────────┼─────────┼─────┐   ┌─────┼─────┼─────┴─────┴─────┴───────┴─────┘
//                                                │ USRNAME │     │   │     │     │
//                                                └─────────┴─────┘   └─────┴─────┘
[SYM] = LAYOUT(
  _______ , _______ , _______ , _______         , _______          , _______ ,                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_GRV  , KC_LABK , KC_RABK         , KC_MINS          , KC_PIPE ,                         KC_CIRC , KC_DLR  , KC_LCBR , KC_RCBR , ARROW   , _______,
  _______ , KC_EXLM , KC_ASTR , LSFT_T(KC_SLSH) , LT(BASE, KC_EQL) , KC_AMPR ,                         KC_HASH , KC_SCLN , KC_LPRN , KC_RPRN , KC_DQUO , _______,
  _______ , KC_TILD , KC_LBRC , KC_RBRC         , KC_PLUS          , KC_PERC ,                         KC_AT   , KC_COLN , KC_COMM , KC_DOT  , KC_QUOT , _______,
                                                                     USRNAME , _______ ,     _______ , _______
),

//    ┌─────┬─────────────┬─────────┬─────────┬─────────┬──────────┐                  ┌─────────┬──────┬─────────┬─────────┬─────────┬─────┐
//    │     │             │         │         │         │          │                  │         │      │         │         │         │     │
//    ├─────┼─────────────┼─────────┼─────────┼─────────┼──────────┤                  ├─────────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │ www_refresh │ C(pgup) │ C(pgdn) │   no    │    no    │                  │  pgup   │ home │   up    │   end   │ SRCHSEL │     │
//    ├─────┼─────────────┼─────────┼─────────┼─────────┼──────────┤                  ├─────────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │    lalt     │  lctl   │  lsft   │ SELLINE │ NOTIMPLE │                  │  pgdn   │ left │  down   │  rght   │   del   │     │
//    ├─────┼─────────────┼─────────┼─────────┼─────────┼──────────┤                  ├─────────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │    lgui     │  pgup   │  pgdn   │   no    │    no    │                  │  C(z)   │ app  │ SELWBAK │ SELWFWD │   no    │     │
//    └─────┴─────────────┴─────────┴─────────┴─────────┼──────────┼────────┐   ┌─────┼─────────┼──────┴─────────┴─────────┴─────────┴─────┘
//                                                      │ www_back │ G(tab) │   │     │ QK_LLCK │
//                                                      └──────────┴────────┘   └─────┴─────────┘
[NAV] = LAYOUT(
  _______ , _______ , _______    , _______    , _______ , _______  ,                           _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_WREF , C(KC_PGUP) , C(KC_PGDN) , XXXXXXX , XXXXXXX  ,                           KC_PGUP , KC_HOME , KC_UP   , KC_END  , SRCHSEL , _______,
  _______ , KC_LALT , KC_LCTL    , KC_LSFT    , SELLINE , NOTIMPLE ,                           KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_DEL  , _______,
  _______ , KC_LGUI , KC_PGUP    , KC_PGDN    , XXXXXXX , XXXXXXX  ,                           C(KC_Z) , KC_APP  , SELWBAK , SELWFWD , XXXXXXX , _______,
                                                          KC_WBAK  , G(KC_TAB) ,     _______ , QK_LLCK
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────────┬─────┬─────┬──────┬──────┬─────┐
//    │     │     │     │     │     │     │             │         │     │     │      │      │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────────┼─────┼─────┼──────┼──────┼─────┤
//    │     │  /  │  9  │  8  │  7  │  *  │             │   no    │ no  │ no  │  no  │  no  │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────────┼─────┼─────┼──────┼──────┼─────┤
//    │     │  -  │  3  │  2  │  1  │  +  │             │   no    │ no  │  e  │ rctl │ lalt │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────────┼─────┼─────┼──────┼──────┼─────┤
//    │     │  x  │  6  │  5  │  4  │  %  │             │   no    │ no  │  ,  │  .   │ lgui │     │
//    └─────┴─────┴─────┴─────┴─────┼─────┼─────┐   ┌───┼─────────┼─────┴─────┴──────┴──────┴─────┘
//                                  │     │     │   │ 0 │ QK_LLCK │
//                                  └─────┴─────┘   └───┴─────────┘
[NUM] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                      _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_SLSH , KC_9    , KC_8    , KC_7    , KC_ASTR ,                      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______,
  _______ , KC_MINS , KC_3    , KC_2    , KC_1    , KC_PLUS ,                      XXXXXXX , XXXXXXX , KC_E    , KC_RCTL , KC_LALT , _______,
  _______ , KC_X    , KC_6    , KC_5    , KC_4    , KC_PERC ,                      XXXXXXX , XXXXXXX , KC_COMM , KC_DOT  , KC_LGUI , _______,
                                                    _______ , _______ ,     KC_0 , QK_LLCK
),

//    ┌─────────┬──────────┬──────┬──────┬──────┬─────────┐                  ┌─────────┬───────────┬────────┬─────┬──────┬────────┐
//    │         │          │      │      │      │         │                  │         │           │        │     │      │        │
//    ├─────────┼──────────┼──────┼──────┼──────┼─────────┤                  ├─────────┼───────────┼────────┼─────┼──────┼────────┤
//    │ RM_TOGG │ NOTIMPLE │ mute │ vold │ volu │ MUTEMIC │                  │   no    │    no     │   no   │ no  │  no  │   no   │
//    ├─────────┼──────────┼──────┼──────┼──────┼─────────┤                  ├─────────┼───────────┼────────┼─────┼──────┼────────┤
//    │ RM_PREV │ RM_NEXT  │ G(3) │ G(2) │ G(1) │  G(d)   │                  │   no    │    no     │  rsft  │ no  │ lalt │   no   │
//    ├─────────┼──────────┼──────┼──────┼──────┼─────────┤                  ├─────────┼───────────┼────────┼─────┼──────┼────────┤
//    │ RM_VALD │ RM_VALU  │ G(6) │ G(5) │ G(4) │  G(w)   │                  │   no    │ S(A(tab)) │ A(tab) │ no  │  no  │ G(ent) │
//    └─────────┴──────────┴──────┴──────┴──────┼─────────┼────────┐   ┌─────┼─────────┼───────────┴────────┴─────┴──────┴────────┘
//                                              │  mply   │ G(spc) │   │     │ QK_LLCK │
//                                              └─────────┴────────┘   └─────┴─────────┘
[WIN] = LAYOUT(
  _______ , _______  , _______ , _______ , _______ , _______ ,                           _______ , _______      , _______   , _______ , _______ , _______  ,
  RM_TOGG , NOTIMPLE , KC_MUTE , KC_VOLD , KC_VOLU , MUTEMIC ,                           XXXXXXX , XXXXXXX      , XXXXXXX   , XXXXXXX , XXXXXXX , XXXXXXX  ,
  RM_PREV , RM_NEXT  , G(KC_3) , G(KC_2) , G(KC_1) , G(KC_D) ,                           XXXXXXX , XXXXXXX      , KC_RSFT   , XXXXXXX , KC_LALT , XXXXXXX  ,
  RM_VALD , RM_VALU  , G(KC_6) , G(KC_5) , G(KC_4) , G(KC_W) ,                           XXXXXXX , S(A(KC_TAB)) , A(KC_TAB) , XXXXXXX , XXXXXXX , G(KC_ENT),
                                                     KC_MPLY , G(KC_SPC) ,     _______ , QK_LLCK
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────────┬────┬──────┬──────┬──────┬────────┐
//    │     │     │     │     │     │     │             │   no    │ no │  no  │  no  │  no  │   no   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────────┼────┼──────┼──────┼──────┼────────┤
//    │ no  │ f12 │ f9  │ f8  │ f7  │ no  │             │   no    │ no │  no  │  no  │  no  │   no   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────────┼────┼──────┼──────┼──────┼────────┤
//    │ no  │ f10 │ f3  │ f2  │ f1  │ no  │             │   no    │ no │ rsft │ rctl │ lalt │   no   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────────┼────┼──────┼──────┼──────┼────────┤
//    │ no  │ f11 │ f6  │ f5  │ f4  │ no  │             │   no    │ no │  no  │  no  │ rgui │ QK_RBT │
//    └─────┴─────┴─────┴─────┴─────┼─────┼────┐   ┌────┼─────────┼────┴──────┴──────┴──────┴────────┘
//                                  │ no  │ no │   │ no │ QK_LLCK │
//                                  └─────┴────┘   └────┴─────────┘
[FUN] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , KC_F12  , KC_F9   , KC_F8   , KC_F7   , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , KC_F10  , KC_F3   , KC_F2   , KC_F1   , XXXXXXX ,                         XXXXXXX , XXXXXXX , KC_RSFT , KC_RCTL , KC_LALT , XXXXXXX,
  XXXXXXX , KC_F11  , KC_F6   , KC_F5   , KC_F4   , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RGUI , QK_RBT ,
                                                    XXXXXXX , XXXXXXX ,     XXXXXXX , QK_LLCK
),

//    ┌──────────┬──────┬──────┬──────┬─────────┬──────────┐                         ┌──────────┬──────────┬──────────┬──────────┬──────────┬─────┐
//    │          │      │      │      │         │          │                         │          │          │          │          │          │     │
//    ├──────────┼──────┼──────┼──────┼─────────┼──────────┤                         ├──────────┼──────────┼──────────┼──────────┼──────────┼─────┤
//    │          │  no  │  no  │  no  │   no    │    no    │                         │ NOTIMPLE │ NOTIMPLE │ NOTIMPLE │ NOTIMPLE │ SRCHSEL  │     │
//    ├──────────┼──────┼──────┼──────┼─────────┼──────────┤                         ├──────────┼──────────┼──────────┼──────────┼──────────┼─────┤
//    │ NOTIMPLE │ lalt │ lctl │ lsft │ SELLINE │    no    │                         │ NOTIMPLE │ NOTIMPLE │ NOTIMPLE │ NOTIMPLE │ NOTIMPLE │     │
//    ├──────────┼──────┼──────┼──────┼─────────┼──────────┤                         ├──────────┼──────────┼──────────┼──────────┼──────────┼─────┤
//    │          │ lgui │ C(v) │ C(a) │  C(c)   │   C(x)   │                         │    no    │    no    │    no    │    no    │    no    │     │
//    └──────────┴──────┴──────┴──────┴─────────┼──────────┼──────────┐   ┌──────────┼──────────┼──────────┴──────────┴──────────┴──────────┴─────┘
//                                              │ www_back │ NOTIMPLE │   │ NOTIMPLE │ QK_LLCK  │
//                                              └──────────┴──────────┘   └──────────┴──────────┘
[EXT] = LAYOUT(
  _______  , _______ , _______ , _______ , _______ , _______ ,                           _______  , _______  , _______  , _______  , _______  , _______,
  _______  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                           NOTIMPLE , NOTIMPLE , NOTIMPLE , NOTIMPLE , SRCHSEL  , _______,
  NOTIMPLE , KC_LALT , KC_LCTL , KC_LSFT , SELLINE , XXXXXXX ,                           NOTIMPLE , NOTIMPLE , NOTIMPLE , NOTIMPLE , NOTIMPLE , _______,
  _______  , KC_LGUI , C(KC_V) , C(KC_A) , C(KC_C) , C(KC_X) ,                           XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______,
                                                     KC_WBAK , NOTIMPLE ,     NOTIMPLE , QK_LLCK
)
};
// clang-format on

///////////////////////////////////////////////////////////////////////////////
// Combos (https://docs.qmk.fm/features/combo)
///////////////////////////////////////////////////////////////////////////////
const uint16_t caps_combo[] PROGMEM   = {KC_COMM, HRM_DOT, COMBO_END};
const uint16_t j_k_combo[] PROGMEM    = {KC_J, KC_K, COMBO_END};
const uint16_t h_comm_combo[] PROGMEM = {KC_H, KC_COMM, COMBO_END};
const uint16_t f_n_combo[] PROGMEM    = {HRM_F, KC_N, COMBO_END};

combo_t key_combos[] = {
    COMBO(caps_combo, CW_TOGG),   // J and , => activate Caps Word.
    COMBO(j_k_combo, KC_BSLS),    // J and K => backslash
    COMBO(h_comm_combo, KC_QUOT), // H and , => '
    COMBO(f_n_combo, OSL(FUN)),   // F and N => FUN layer
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods     = get_mods();
    const uint8_t all_mods = (mods | get_weak_mods()
#ifndef NO_ACTION_ONESHOT
                              | get_oneshot_mods()
#endif // NO_ACTION_ONESHOT
    );
    const uint8_t shift_mods = all_mods & MOD_MASK_SHIFT;
    const bool    alt        = all_mods & MOD_BIT_LALT;

    if (record->event.pressed) {
        switch (keycode) {
            case USRNAME:
                SEND_STRING("omareloui");
                return true;

            case SRCHSEL: // Searches the current selection in a new tab.
                // Mac users, change LCTL to LGUI.
                SEND_STRING_DELAY(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER), TAP_CODE_DELAY);
                return false;

            case ARROW:                                                   // Unicode arrows -> => <-> <=> through Shift and Alt.
                send_unicode_string(alt ? (shift_mods ? "\xe2\x87\x94"    // <=>
                                                      : "\xe2\x86\x94")   // <->
                                        : (shift_mods ? "\xe2\x87\x92"    // =>
                                                      : "\xe2\x86\x92")); // ->
                return false;
        }
    }

    switch (keycode) {
        case SELWBAK: // Backward word selection.
            if (record->event.pressed) {
                select_word_register('B');
            } else {
                select_word_unregister();
            }
            break;

        case SELWFWD: // Forward word selection.
            if (record->event.pressed) {
                select_word_register('W');
            } else {
                select_word_unregister();
            }
            break;

        case SELLINE: // Line selection.
            if (record->event.pressed) {
                select_word_register('L');
            } else {
                select_word_unregister();
            }

            break;

        // Behavior:
        //  * Unmodified:       _ (KC_UNDS)
        //  * With Shift:       - (KC_MINS)
        //  * With Alt:         Unicode en dash
        //  * With Shift + Alt: Unicode em dash
        case KC_UNDS: {
            static uint16_t registered_keycode = KC_NO;

            if (record->event.pressed) {
                if (alt) {
                    send_unicode_string(shift_mods ? "\xe2\x80\x94" : "\xe2\x80\x93");
                } else {
                    process_caps_word(keycode, record);
                    const bool shifted = (mods | get_weak_mods()) & MOD_MASK_SHIFT;
                    clear_weak_mods();
                    clear_mods();

                    if (registered_keycode) { // Invoked through Repeat key.
                        unregister_code16(registered_keycode);
                    } else {
                        registered_keycode = shifted ? KC_MINS : KC_UNDS;
                    }

                    register_code16(registered_keycode);
                    set_mods(mods);
                }
            } else if (registered_keycode) {
                unregister_code16(registered_keycode);
                registered_keycode = KC_NO;
            }
        }
            return false;
    }

    return true;
};
