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
    STRDY,
    QWERTY,
    SYM,
    NAV,
    NUM,
    WIN,
    FUN,
    EXT,
};

enum custom_keycodes {
    USRNAME = SAFE_RANGE,
    UPDIR,
    SRCHSEL,
    ARROW,
    SELLINE,
    SELWBAK,
    SELWFWD,
    // Macros invoked through the Magic key.
    M_DOCSTR,
    M_EQEQ,
    M_INCLUDE,
    M_ION,
    M_MENT,
    M_MKGRVS,
    M_QUEN,
    M_THE,
    M_TMENT,
    M_UPDIR,
    M_NBSP,
    M_NOOP,
};

#define MAGIC QK_AREP

#define NOTIMPLE KC_NO
#define MUTEMIC KC_F20

#define QRTY_HRM_F LT(NAV, KC_F)
#define QRTY_HRM_J LT(NUM, KC_J)
#define QRTY_HRM_K RSFT_T(KC_K)
#define QRTY_HRM_D LSFT_T(KC_D)

#define HRM_S LALT_T(KC_S)
#define HRM_T LT(SYM, KC_T)
#define HRM_R LSFT_T(KC_R)
#define HRM_D LT(NAV, KC_D)
#define HRM_G LCTL_T(KC_G)
#define HRM_X LGUI_T(KC_X)

#define HRM_N LT(NUM, KC_N)
#define HRM_E RSFT_T(KC_E)
#define HRM_A LT(SYM, KC_A)
#define HRM_I LALT_T(KC_I)
#define HRM_H RCTL_T(KC_H)
#define HRM_DOT LT(WIN, KC_DOT)
#define HRM_QUO RGUI_T(KC_QUOT)

#define EXT_COL LT(EXT, KC_SCLN)
#define NAV_SLS LSFT_T(KC_SLSH)
#define NAV_EQL LT(0, KC_EQL)

#ifdef CHORDAL_HOLD
// clang-format off
// Handedness for Chordal Hold (https://github.com/qmk/qmk_firmware/pull/24560)
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  '*', '*', '*', '*', '*', '*',              '*', '*', '*', '*', '*', '*',
  '*', 'L', 'L', 'L', 'L', 'L',              'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',              'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',              'R', 'R', 'R', 'R', 'R', '*',
                           'L', 'L',    'R', 'R'
);
// clang-format on
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────┬─────────┬───────┬───────┬───────┬──────────┐                  ┌──────┬───────┬───────┬─────────┬─────────┬────────────┐
//    │    `    │ SELLINE │ C(v)  │ C(a)  │ C(c)  │ NOTIMPLE │                  │ home │ left  │ rght  │   end   │ G(tab)  │ DF(QWERTY) │
//    ├─────────┼─────────┼───────┼───────┼───────┼──────────┤                  ├──────┼───────┼───────┼─────────┼─────────┼────────────┤
//    │   tab   │    v    │   m   │   l   │   c   │    p     │                  │  b   │ MAGIC │   u   │    o    │    q    │     /      │
//    ├─────────┼─────────┼───────┼───────┼───────┼──────────┤                  ├──────┼───────┼───────┼─────────┼─────────┼────────────┤
//    │  bspc   │  HRM_S  │ HRM_T │ HRM_R │ HRM_D │    y     │                  │  f   │ HRM_N │ HRM_E │  HRM_A  │  HRM_I  │     -      │
//    ├─────────┼─────────┼───────┼───────┼───────┼──────────┤                  ├──────┼───────┼───────┼─────────┼─────────┼────────────┤
//    │ EXT_COL │  HRM_X  │   k   │   j   │ HRM_G │    w     │                  │  z   │ HRM_H │   ,   │ HRM_DOT │ HRM_QUO │    ent     │
//    └─────────┴─────────┴───────┴───────┴───────┼──────────┼─────┐   ┌────────┼──────┼───────┴───────┴─────────┴─────────┴────────────┘
//                                                │    _     │ spc │   │ QK_REP │ esc  │
//                                                └──────────┴─────┘   └────────┴──────┘
[STRDY] = LAYOUT(
  KC_GRV  , SELLINE , C(KC_V) , C(KC_A) , C(KC_C) , NOTIMPLE ,                       KC_HOME , KC_LEFT , KC_RGHT , KC_END  , G(KC_TAB) , DF(QWERTY),
  KC_TAB  , KC_V    , KC_M    , KC_L    , KC_C    , KC_P     ,                       KC_B    , MAGIC   , KC_U    , KC_O    , KC_Q      , KC_SLSH   ,
  KC_BSPC , HRM_S   , HRM_T   , HRM_R   , HRM_D   , KC_Y     ,                       KC_F    , HRM_N   , HRM_E   , HRM_A   , HRM_I     , KC_MINS   ,
  EXT_COL , HRM_X   , KC_K    , KC_J    , HRM_G   , KC_W     ,                       KC_Z    , HRM_H   , KC_COMM , HRM_DOT , HRM_QUO   , KC_ENT    ,
                                                    KC_UNDS  , KC_SPC ,     QK_REP , KC_ESC
),

//    ┌─────────┬───────────┬────────────┬────────────┬────────────┬──────────┐                  ┌──────┬────────────┬────────────┬────────────┬───────────┬───────────┐
//    │    `    │  SELLINE  │    C(v)    │    C(a)    │    C(c)    │ NOTIMPLE │                  │ home │    left    │    rght    │    end     │  G(tab)   │ DF(STRDY) │
//    ├─────────┼───────────┼────────────┼────────────┼────────────┼──────────┤                  ├──────┼────────────┼────────────┼────────────┼───────────┼───────────┤
//    │   tab   │     q     │     w      │     e      │     r      │    t     │                  │  y   │     u      │     i      │     o      │     p     │     /     │
//    ├─────────┼───────────┼────────────┼────────────┼────────────┼──────────┤                  ├──────┼────────────┼────────────┼────────────┼───────────┼───────────┤
//    │  bspc   │ LALT_T(a) │ LT(SYM, s) │ QRTY_HRM_D │ QRTY_HRM_F │    g     │                  │  h   │ QRTY_HRM_J │ QRTY_HRM_K │ LT(SYM, l) │ LALT_T(;) │     -     │
//    ├─────────┼───────────┼────────────┼────────────┼────────────┼──────────┤                  ├──────┼────────────┼────────────┼────────────┼───────────┼───────────┤
//    │ MO(EXT) │ LGUI_T(z) │     x      │     c      │ LCTL_T(v)  │    b     │                  │  n   │ RCTL_T(m)  │     ,      │  HRM_DOT   │ RGUI_T(/) │    ent    │
//    └─────────┴───────────┴────────────┴────────────┴────────────┼──────────┼─────┐   ┌────────┼──────┼────────────┴────────────┴────────────┴───────────┴───────────┘
//                                                                 │    _     │ spc │   │ QK_REP │ esc  │
//                                                                 └──────────┴─────┘   └────────┴──────┘
[QWERTY] = LAYOUT(
  KC_GRV  , SELLINE      , C(KC_V)       , C(KC_A)    , C(KC_C)      , NOTIMPLE ,                       KC_HOME , KC_LEFT      , KC_RGHT    , KC_END        , G(KC_TAB)       , DF(STRDY),
  KC_TAB  , KC_Q         , KC_W          , KC_E       , KC_R         , KC_T     ,                       KC_Y    , KC_U         , KC_I       , KC_O          , KC_P            , KC_SLSH  ,
  KC_BSPC , LALT_T(KC_A) , LT(SYM, KC_S) , QRTY_HRM_D , QRTY_HRM_F   , KC_G     ,                       KC_H    , QRTY_HRM_J   , QRTY_HRM_K , LT(SYM, KC_L) , LALT_T(KC_SCLN) , KC_MINS  ,
  MO(EXT) , LGUI_T(KC_Z) , KC_X          , KC_C       , LCTL_T(KC_V) , KC_B     ,                       KC_N    , RCTL_T(KC_M) , KC_COMMA   , HRM_DOT       , RGUI_T(KC_SLSH) , KC_ENT   ,
                                                                       KC_UNDS  , KC_SPC ,     QK_REP , KC_ESC
),

//    ┌─────┬─────┬─────┬───────────┬──────────────┬─────────┐               ┌─────┬─────┬─────┬─────┬───────┬─────┐
//    │     │     │     │           │              │         │               │     │     │     │     │       │     │
//    ├─────┼─────┼─────┼───────────┼──────────────┼─────────┤               ├─────┼─────┼─────┼─────┼───────┼─────┤
//    │     │  `  │  <  │     >     │      -       │    |    │               │  ^  │  $  │  {  │  }  │ ARROW │     │
//    ├─────┼─────┼─────┼───────────┼──────────────┼─────────┤               ├─────┼─────┼─────┼─────┼───────┼─────┤
//    │     │  !  │  *  │ LSFT_T(/) │ LT(STRDY, =) │    &    │               │  #  │  ;  │  (  │  )  │   "   │     │
//    ├─────┼─────┼─────┼───────────┼──────────────┼─────────┤               ├─────┼─────┼─────┼─────┼───────┼─────┤
//    │     │  ~  │  [  │     ]     │      +       │    %    │               │  @  │  :  │  ,  │  .  │   '   │     │
//    └─────┴─────┴─────┴───────────┴──────────────┼─────────┼─────┐   ┌─────┼─────┼─────┴─────┴─────┴───────┴─────┘
//                                                 │ USRNAME │     │   │     │     │
//                                                 └─────────┴─────┘   └─────┴─────┘
[SYM] = LAYOUT(
  _______ , _______ , _______ , _______         , _______           , _______ ,                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_GRV  , KC_LABK , KC_RABK         , KC_MINS           , KC_PIPE ,                         KC_CIRC , KC_DLR  , KC_LCBR , KC_RCBR , ARROW   , _______,
  _______ , KC_EXLM , KC_ASTR , LSFT_T(KC_SLSH) , LT(STRDY, KC_EQL) , KC_AMPR ,                         KC_HASH , KC_SCLN , KC_LPRN , KC_RPRN , KC_DQUO , _______,
  _______ , KC_TILD , KC_LBRC , KC_RBRC         , KC_PLUS           , KC_PERC ,                         KC_AT   , KC_COLN , KC_COMM , KC_DOT  , KC_QUOT , _______,
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

// A cheap pseudorandom generator.
uint8_t myrand(void) {
    static uint16_t state = 1;
    state                 = UINT16_C(36563) * (state + timer_read());
    return state >> 8;
}

///////////////////////////////////////////////////////////////////////////////
// Combos (https://docs.qmk.fm/features/combo)
///////////////////////////////////////////////////////////////////////////////
const uint16_t j_comm_combo[] PROGMEM   = {KC_J, KC_COMM, COMBO_END};
const uint16_t j_k_combo[] PROGMEM      = {KC_J, KC_K, COMBO_END};
const uint16_t h_comm_combo[] PROGMEM   = {HRM_H, KC_COMM, COMBO_END};
const uint16_t comm_dot_combo[] PROGMEM = {KC_COMM, HRM_DOT, COMBO_END};
const uint16_t f_n_combo[] PROGMEM      = {KC_F, HRM_N, COMBO_END};

combo_t key_combos[] = {
    COMBO(j_comm_combo, CW_TOGG),   // J and , => activate Caps Word.
    COMBO(j_k_combo, KC_BSLS),      // J and K => backslash
    COMBO(h_comm_combo, KC_QUOT),   // H and , => '
    COMBO(comm_dot_combo, CW_TOGG), // , and . => activate Caps Word in QWERTY layer.
    /* COMBO(comm_dot_combo, KC_SCLN), // , and . => ; */
    COMBO(f_n_combo, OSL(FUN)), // F and N => FUN layer
};

///////////////////////////////////////////////////////////////////////////////
// Tap-hold configuration (https://docs.qmk.fm/tap_hold)
///////////////////////////////////////////////////////////////////////////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QRTY_HRM_D:
        case QRTY_HRM_K:
        case HRM_R:
        case HRM_E:
            return TAPPING_TERM - 45;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    // If you quickly hold a tap-hold key after tapping it, the tap action is
    // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
    // lead to missed triggers in fast typing. Here, returning 0 means we
    // instead want to "force hold" and disable key repeating.
    switch (keycode) {
        case HRM_N:
        case HRM_H:
        case QRTY_HRM_J:
        case QRTY_HRM_K:
            return QUICK_TAP_TERM; // Enable key repeating.
        default:
            return 0; // Otherwise, force hold and disable key repeating.
    }
}

///////////////////////////////////////////////////////////////////////////////
// Repeat key (https://docs.qmk.fm/features/repeat_key)
///////////////////////////////////////////////////////////////////////////////
bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    // Unpack tapping keycode for tap-hold keys.
    switch (keycode) {
#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;
#    ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
#    endif // NO_ACTION_LAYER
#endif     // NO_ACTION_TAPPING
    }

#ifdef SENTENCE_CASE_ENABLE
    if (is_sentence_case_primed() && sentence_case_press_user(keycode, record, *remembered_mods) == 'a') {
        *remembered_mods |= MOD_BIT_LSHIFT;
    }
#endif // SENTENCE_CASE_ENABLE

    // Forget Shift on most letters when Shift or AltGr are the only mods. Some
    // letters are excluded, e.g. for "NN" and "ZZ" in Vim.
    switch (keycode) {
        case KC_A ... KC_H:
        case KC_K ... KC_M:
        case KC_O ... KC_U:
            if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT_RALT)) == 0) {
                *remembered_mods &= ~MOD_MASK_SHIFT;
            }
            break;
    }

    return true;
}

// The following describes the magic key functionality, where * represents the
// magic key and @ the repeat key. For example, tapping A and then the magic key
// types "ao". Most of this is coded in my `get_alt_repeat_key_keycode_user()`
// definition below.
//
// SFB removal and common n-grams:
//
//     A * -> AO     L * -> LK      S * -> SK
//     C * -> CY     M * -> MENT    T * -> TMENT
//     D * -> DY     O * -> OA      U * -> UE
//     E * -> EU     P * -> PY      Y * -> YP
//     G * -> GY     Q * -> QUEN    spc * -> THE
//     I * -> ION    R * -> RL
//
// When the magic key types a letter, following it with the repeat key produces
// "n". This is useful to type certain patterns without SFBs.
//
//     A * @ -> AON             (like "kaon")
//     D * @ -> DYN             (like "dynamic")
//     E * @ -> EUN             (like "reunite")
//     O * @ -> OAN             (like "loan")
//
// Other patterns:
//
//     spc * @ -> THEN
//     I * @ -> IONS            (like "nations")
//     M * @ -> MENTS           (like "moments")
//     Q * @ -> QUENC           (like "frequency")
//     T * @ -> TMENTS          (like "adjustments")
//     = *   -> ===             (JS code)
//     ! *   -> !==             (JS code)
//     " *   -> """<cursor>"""  (Python code)
//     ` *   -> ```<cursor>```  (Markdown code)
//     # *   -> #include        (C code)
//     & *   -> &nbsp;          (HTML code)
//     . *   -> ../             (shell)
//     . * @ -> ../../
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if (mods == MOD_BIT_LALT) {
        switch (keycode) {
            case KC_U:
                return A(KC_O);
            case KC_O:
                return A(KC_U);
            case HRM_N:
                return A(KC_I);
            case HRM_I:
                return A(KC_N);
        }
    } else if ((mods & ~MOD_MASK_SHIFT) == 0) {
        // This is where most of the "magic" for the MAGIC key is implemented.
        switch (keycode) {
            case KC_SPC: // spc -> THE
            case KC_ENT:
            case KC_TAB:
                return M_THE;

            // For navigating next/previous search results in Vim:
            // N -> Shift + N, Shift + N -> N.
            case HRM_N:
                if ((mods & MOD_MASK_SHIFT) == 0) {
                    return S(KC_N);
                }
                // Fall through intended.
            case KC_N:
                return KC_N;

            // Fix SFBs and awkward strokes.
            case HRM_A:
                return KC_O; // A -> O
            case KC_O:
                return KC_A; // O -> A
            case HRM_E:
                return KC_U; // E -> U
            case KC_U:
                return KC_E; // U -> E
            case HRM_I:
                if ((mods & MOD_MASK_SHIFT) == 0) {
                    return M_ION; // I -> ON
                } else {
                    return KC_QUOT; // Shift I -> '
                }
            case KC_M:
                return M_MENT; // M -> ENT
            case KC_Q:
                return M_QUEN; // Q -> UEN
            case HRM_T:
                return M_TMENT; // T -> TMENT

            case KC_C:
                return KC_Y; // C -> Y
            case HRM_D:
                return KC_Y; // D -> Y
            case HRM_G:
                return KC_Y; // G -> Y
            case KC_P:
                return KC_Y; // P -> Y
            case KC_Y:
                return KC_P; // Y -> P

            case KC_L:
                return KC_K; // L -> K
            case HRM_S:
                return KC_K; // S -> K

            case HRM_R:
                return KC_L; // R -> L
            case HRM_DOT:
                if ((mods & MOD_MASK_SHIFT) == 0) {
                    return M_UPDIR; // . -> ./
                }
                return M_NOOP;
            case KC_HASH:
                return M_INCLUDE; // # -> include
            case KC_AMPR:
                return M_NBSP; // & -> nbsp;
            case KC_EQL:
                return M_EQEQ; // = -> ==
            case KC_RBRC:
                return KC_SCLN; // ] -> ;
            case KC_AT:
                return USRNAME; // @ -> <username>

            case KC_COMM:
                if ((mods & MOD_MASK_SHIFT) != 0) {
                    return KC_EQL; // ! -> =
                }
                return M_NOOP;
            case HRM_QUO:
                if ((mods & MOD_MASK_SHIFT) != 0) {
                    return M_DOCSTR; // " -> ""<cursor>"""
                }
                return M_NOOP;
            case KC_GRV: // ` -> ``<cursor>``` (for Markdown code)
                return M_MKGRVS;
            case KC_LABK: // < -> - (for Haskell)
                return KC_MINS;
            case KC_SLSH:
                return KC_SLSH; // / -> / (easier reach than Repeat)

            case KC_PLUS:
            case KC_MINS:
            case KC_ASTR:
            case KC_PERC:
            case KC_PIPE:
            case KC_CIRC:
            case KC_TILD:
            case KC_EXLM:
            case KC_DLR:
            case KC_RABK:
            case KC_LPRN:
            case KC_RPRN:
            case KC_UNDS:
            case KC_COLN:
                return KC_EQL;

            case KC_F:
            case KC_V:
            case HRM_X:
            case KC_SCLN:
            case KC_1 ... KC_0:
                return M_NOOP;
        }
    }

    switch (keycode) {
        case KC_WH_U:
            return KC_WH_D;
        case KC_WH_D:
            return KC_WH_U;
        case SELWBAK:
            return SELWFWD;
        case SELWFWD:
            return SELWBAK;
    }
    return KC_TRNS;
}

// An enhanced version of SEND_STRING: if Caps Word is active, the Shift key is
// held while sending the string. Additionally, the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`. This helper is
// used for several macros below in my process_record_user() function.
#define MAGIC_STRING(str, repeat_keycode) magic_send_string_P(PSTR(str), (repeat_keycode))
static void magic_send_string_P(const char *str, uint16_t repeat_keycode) {
    uint8_t saved_mods = 0;
    // If Caps Word is on, save the mods and hold Shift.
    if (is_caps_word_on()) {
        saved_mods = get_mods();
        register_mods(MOD_BIT_LSHIFT);
    }

    send_string_P(str); // Send the string.
    set_last_keycode(repeat_keycode);

    // If Caps Word is on, restore the mods.
    if (is_caps_word_on()) {
        set_mods(saved_mods);
    }
}

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
            case UPDIR:
                SEND_STRING_DELAY("../", TAP_CODE_DELAY);
                return false;

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

            // Macros invoked through the MAGIC key.
            case M_THE:
                MAGIC_STRING(/* */ "the", KC_N);
                break;
            case M_ION:
                MAGIC_STRING(/*i*/ "on", KC_S);
                break;
            case M_MENT:
                MAGIC_STRING(/*m*/ "ent", KC_S);
                break;
            case M_QUEN:
                MAGIC_STRING(/*q*/ "uen", KC_C);
                break;
            case M_TMENT:
                MAGIC_STRING(/*t*/ "ment", KC_S);
                break;
            case M_UPDIR:
                MAGIC_STRING(/*.*/ "./", UPDIR);
                break;
            case M_INCLUDE:
                SEND_STRING_DELAY(/*#*/ "include ", TAP_CODE_DELAY);
                break;
            case M_EQEQ:
                SEND_STRING_DELAY(/*=*/"==", TAP_CODE_DELAY);
                break;
            case M_NBSP:
                SEND_STRING_DELAY(/*&*/ "nbsp;", TAP_CODE_DELAY);
                break;

            case M_DOCSTR:
                SEND_STRING_DELAY(/*"*/ "\"\"\"\"\"" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT), TAP_CODE_DELAY);
                break;
            case M_MKGRVS:
                SEND_STRING_DELAY(/*`*/ "``\n\n```" SS_TAP(X_UP), TAP_CODE_DELAY);
                break;

            case KC_RABK:
                if (shift_mods) { // Shift + > types a happy emoji.
                    static const char *emojis[] = {
                        "\xf0\x9f\xa5\xb3", // Party hat.
                        "\xf0\x9f\x91\x8d", // Thumbs up.
                        "\xe2\x9c\x8c",     // Victory hand.
                        "\xf0\x9f\xa4\xa9", // Star eyes.
                        "\xf0\x9f\x94\xa5", // Fire.
                        "\xf0\x9f\x8e\x89", // Party popper.
                        "\xf0\x9f\x91\xbe", // Purple alien.
                        "\xf0\x9f\x98\x81", // Grin.
                    };
                    const int NUM_EMOJIS = sizeof(emojis) / sizeof(*emojis);

                    // Pick an index between 0 and NUM_EMOJIS - 2.
                    uint8_t index = ((NUM_EMOJIS - 1) * myrand()) >> 8;
                    // Don't pick the same emoji twice in a row.
                    static uint8_t last_index = 0;
                    if (index >= last_index) {
                        ++index;
                    }
                    last_index = index;

                    // Produce the emoji.
                    send_unicode_string(emojis[index]);
                    return false;
                }
                return true;
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

void housekeeping_task_user(void) {
#ifdef ACHORDION_ENABLE
    achordion_task();
#endif // ACHORDION_ENABLE
/* #ifdef RGB_MATRIX_ENABLE */
/*     lighting_task(); */
/* #endif // RGB_MATRIX_ENABLE */
#ifdef ORBITAL_MOUSE_ENABLE
    orbital_mouse_task();
#endif // ORBITAL_MOUSE_ENABLE
#ifdef SELECT_WORD_ENABLE
    select_word_task();
#endif // SELECT_WORD_ENABLE
#ifdef SENTENCE_CASE_ENABLE
    sentence_case_task();
#endif // SENTENCE_CASE_ENABLE
}
