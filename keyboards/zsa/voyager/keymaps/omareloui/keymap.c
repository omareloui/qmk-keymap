// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2025 Omar Eloui  (@omareloui) <contact@omareloui.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "palettefx.h"
#include "report.h"
#include QMK_KEYBOARD_H

enum layers {
    STRDY,
    GAME,
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
    RM_RND,
    RM_DEF1,
    RM_DEF2,

    // Symbols
    SYM_ARROW,
    SYM_FAT_ARROW,
    SYM_POUND_SIGN,
    SYM_DBLAMPR,
    SYM_DBLPIPE,
    SYM_GOASS,
    SYM_RPRN_AND_NEW_BLOCK,
    SYM_TEMPLATE_STRING,
    SYM_MULTILINE_COMMENT,

    // Macros invoked through the Magic key.
    M_ION,
    M_MENT,
    M_QUEN,
    M_THE,
    M_TMENT,
    M_DOCSTR,
    M_EQEQ,
    M_MKGRVS,
    M_INCLUDE,
    M_NBSP,
    M_UPDIR,
    M_BRC,
    M_ABK,
    M_CBR,
    M_PRN,
    M_NOOP,

    LUM_CYC,

    O_EMAIL,
    O_CD_EMAIL,
    O_SEC,
    O_ID,

    PASTE_ENTER,

#ifdef ENABLE_MOUSE_JIGGLER
    JIGGLE,
#endif
};

// Matrix positions of the left home row keys.
#define LEFT_HOME_ROW 2
#define LEFT_HOME_PINKY_COL 2
#define LEFT_HOME_RING_COL 3
#define LEFT_HOME_MIDDLE_COL 4
#define LEFT_HOME_INDEX_COL 5

#define MAGIC QK_AREP

#define NOTIMPLE KC_NO
#define MUTEMIC KC_F20

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

#define COPY C(KC_C)
#define CUT C(KC_X)
#define PASTE C(KC_V)
#define UNDO C(KC_Z)
#define SELALL C(KC_A)
#define WWW_PRV_TAB C(KC_PGUP)
#define WWW_NXT_TAB C(KC_PGDN)

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
//    ┌─────────┬─────────┬───────┬────────┬───────┬─────────┐                  ┌────────┬───────┬───────┬─────────┬─────────┬──────────┐
//    │    `    │ SELLINE │ PASTE │ SELALL │ COPY  │ OM_BTN1 │                  │ G(tab) │ home  │ left  │  rght   │   end   │ DF(GAME) │
//    ├─────────┼─────────┼───────┼────────┼───────┼─────────┤                  ├────────┼───────┼───────┼─────────┼─────────┼──────────┤
//    │   tab   │    v    │   m   │   l    │   c   │    p    │                  │   b    │ MAGIC │   u   │    o    │    q    │    /     │
//    ├─────────┼─────────┼───────┼────────┼───────┼─────────┤                  ├────────┼───────┼───────┼─────────┼─────────┼──────────┤
//    │  bspc   │  HRM_S  │ HRM_T │ HRM_R  │ HRM_D │    y    │                  │   f    │ HRM_N │ HRM_E │  HRM_A  │  HRM_I  │    -     │
//    ├─────────┼─────────┼───────┼────────┼───────┼─────────┤                  ├────────┼───────┼───────┼─────────┼─────────┼──────────┤
//    │ EXT_COL │  HRM_X  │   k   │   j    │ HRM_G │    w    │                  │   z    │ HRM_H │   ,   │ HRM_DOT │ HRM_QUO │   ent    │
//    └─────────┴─────────┴───────┴────────┴───────┼─────────┼─────┐   ┌────────┼────────┼───────┴───────┴─────────┴─────────┴──────────┘
//                                                 │    _    │ spc │   │ QK_REP │  esc   │
//                                                 └─────────┴─────┘   └────────┴────────┘
[STRDY] = LAYOUT(
  KC_GRV  , SELLINE , PASTE , SELALL , COPY  , OM_BTN1 ,                       G(KC_TAB) , KC_HOME , KC_LEFT , KC_RGHT , KC_END  , DF(GAME),
  KC_TAB  , KC_V    , KC_M  , KC_L   , KC_C  , KC_P    ,                       KC_B      , MAGIC   , KC_U    , KC_O    , KC_Q    , KC_SLSH ,
  KC_BSPC , HRM_S   , HRM_T , HRM_R  , HRM_D , KC_Y    ,                       KC_F      , HRM_N   , HRM_E   , HRM_A   , HRM_I   , KC_MINS ,
  EXT_COL , HRM_X   , KC_K  , KC_J   , HRM_G , KC_W    ,                       KC_Z      , HRM_H   , KC_COMM , HRM_DOT , HRM_QUO , KC_ENT  ,
                                               KC_UNDS , KC_SPC ,     QK_REP , KC_ESC
),

//    ┌──────┬──────┬──────┬──────┬──────┬───────┐              ┌────┬────┬────┬────┬────┬───────────┐
//    │ esc  │  1   │  2   │  3   │  4   │   5   │              │ 6  │ 7  │ 8  │ 9  │ 0  │ DF(STRDY) │
//    ├──────┼──────┼──────┼──────┼──────┼───────┤              ├────┼────┼────┼────┼────┼───────────┤
//    │ tab  │  no  │  q   │  up  │  e   │   r   │              │ no │ no │ no │ no │ no │    no     │
//    ├──────┼──────┼──────┼──────┼──────┼───────┤              ├────┼────┼────┼────┼────┼───────────┤
//    │ lsft │  no  │ left │ down │ rght │  no   │              │ no │ no │ no │ no │ no │    no     │
//    ├──────┼──────┼──────┼──────┼──────┼───────┤              ├────┼────┼────┼────┼────┼───────────┤
//    │ ent  │ rctl │  no  │  no  │  no  │  no   │              │ no │ no │ no │ no │ no │    no     │
//    └──────┴──────┴──────┴──────┴──────┼───────┼─────┐   ┌────┼────┼────┴────┴────┴────┴───────────┘
//                                       │ TURBO │ spc │   │ no │ no │
//                                       └───────┴─────┘   └────┴────┘
[GAME] = LAYOUT(
  KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                        KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , DF(STRDY),
  KC_TAB  , XXXXXXX , KC_Q    , KC_UP   , KC_E    , KC_R    ,                        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,
  KC_LSFT , XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX ,                        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,
  KC_ENT  , KC_RCTL , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  ,
                                                    TURBO   , KC_SPC ,     XXXXXXX , XXXXXXX
),

//    ┌─────┬─────┬─────┬─────┬───────┬─────────┐               ┌──────┬─────┬─────┬─────┬─────┬─────┐
//    │     │     │     │     │       │         │               │      │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼───────┼─────────┤               ├──────┼─────┼─────┼─────┼─────┼─────┤
//    │     │  ^  │  <  │  [  │ MAGIC │    `    │               │  &   │  +  │  ]  │  >  │  $  │     │
//    ├─────┼─────┼─────┼─────┼───────┼─────────┤               ├──────┼─────┼─────┼─────┼─────┼─────┤
//    │     │  =  │  (  │  {  │   /   │    ~    │               │  -   │  \  │  }  │  )  │  ;  │     │
//    ├─────┼─────┼─────┼─────┼───────┼─────────┤               ├──────┼─────┼─────┼─────┼─────┼─────┤
//    │     │  @  │  '  │  "  │   #   │    %    │               │  |   │  *  │  !  │  ?  │  :  │     │
//    └─────┴─────┴─────┴─────┴───────┼─────────┼─────┐   ┌─────┼──────┼─────┴─────┴─────┴─────┴─────┘
//                                    │ USRNAME │     │   │     │ lock │
//                                    └─────────┴─────┘   └─────┴──────┘
[SYM] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_CIRC , KC_LABK , KC_LBRC , MAGIC   , KC_GRV  ,                         KC_AMPR , KC_PLUS , KC_RBRC , KC_RABK , KC_DLR  , _______,
  _______ , KC_EQL  , KC_LPRN , KC_LCBR , KC_SLSH , KC_TILD ,                         KC_MINS , KC_BSLS , KC_RCBR , KC_RPRN , KC_SCLN , _______,
  _______ , KC_AT   , KC_QUOT , KC_DQUO , KC_HASH , KC_PERC ,                         KC_PIPE , KC_ASTR , KC_EXLM , KC_QUES , KC_COLN , _______,
                                                    USRNAME , _______ ,     _______ , QK_LLCK
),

//    ┌─────┬─────────────┬─────────────┬─────────────┬─────────┬──────────┐                  ┌──────┬──────┬─────────┬─────────┬─────────┬─────┐
//    │     │             │             │             │         │          │                  │      │      │         │         │         │     │
//    ├─────┼─────────────┼─────────────┼─────────────┼─────────┼──────────┤                  ├──────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │ www_refresh │ WWW_PRV_TAB │ WWW_NXT_TAB │   no    │    no    │                  │ pgup │ home │   up    │   end   │ SRCHSEL │     │
//    ├─────┼─────────────┼─────────────┼─────────────┼─────────┼──────────┤                  ├──────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │    lalt     │  S(A(tab))  │   A(tab)    │ SELLINE │ OM_BTN1  │                  │ pgdn │ left │  down   │  rght   │   del   │     │
//    ├─────┼─────────────┼─────────────┼─────────────┼─────────┼──────────┤                  ├──────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │    lgui     │    pgup     │    pgdn     │   no    │    no    │                  │ UNDO │ app  │ SELWBAK │ SELWORD │   no    │     │
//    └─────┴─────────────┴─────────────┴─────────────┴─────────┼──────────┼────────┐   ┌─────┼──────┼──────┴─────────┴─────────┴─────────┴─────┘
//                                                              │ www_back │ G(tab) │   │     │ lock │
//                                                              └──────────┴────────┘   └─────┴──────┘
[NAV] = LAYOUT(
  _______ , _______ , _______      , _______     , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_WREF , WWW_PRV_TAB  , WWW_NXT_TAB , XXXXXXX , XXXXXXX ,                           KC_PGUP , KC_HOME , KC_UP   , KC_END  , SRCHSEL , _______,
  _______ , KC_LALT , S(A(KC_TAB)) , A(KC_TAB)   , SELLINE , OM_BTN1 ,                           KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_DEL  , _______,
  _______ , KC_LGUI , KC_PGUP      , KC_PGDN     , XXXXXXX , XXXXXXX ,                           UNDO    , KC_APP  , SELWBAK , SELWORD , XXXXXXX , _______,
                                                             KC_WBAK , G(KC_TAB) ,     _______ , QK_LLCK
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌──────┬─────┬─────┬──────┬──────┬─────┐
//    │     │     │     │     │     │     │             │      │     │     │      │      │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├──────┼─────┼─────┼──────┼──────┼─────┤
//    │     │  /  │  9  │  8  │  7  │  *  │             │  no  │ no  │ no  │  no  │  no  │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├──────┼─────┼─────┼──────┼──────┼─────┤
//    │     │  -  │  3  │  2  │  1  │  +  │             │  no  │ no  │  e  │ rctl │ lalt │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├──────┼─────┼─────┼──────┼──────┼─────┤
//    │     │  x  │  6  │  5  │  4  │  %  │             │  no  │ no  │  ,  │  .   │ lgui │     │
//    └─────┴─────┴─────┴─────┴─────┼─────┼─────┐   ┌───┼──────┼─────┴─────┴──────┴──────┴─────┘
//                                  │     │     │   │ 0 │ lock │
//                                  └─────┴─────┘   └───┴──────┘
[NUM] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                      _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_SLSH , KC_9    , KC_8    , KC_7    , KC_ASTR ,                      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______,
  _______ , KC_MINS , KC_3    , KC_2    , KC_1    , KC_PLUS ,                      XXXXXXX , XXXXXXX , KC_E    , KC_RCTL , KC_LALT , _______,
  _______ , KC_X    , KC_6    , KC_5    , KC_4    , KC_PERC ,                      XXXXXXX , XXXXXXX , KC_COMM , KC_DOT  , KC_LGUI , _______,
                                                    _______ , _______ ,     KC_0 , QK_LLCK
),

//    ┌─────────┬─────────┬──────┬──────┬──────┬─────────┐                  ┌──────┬───────────┬────────┬─────┬──────┬────────┐
//    │         │         │      │      │      │         │                  │      │           │        │     │      │        │
//    ├─────────┼─────────┼──────┼──────┼──────┼─────────┤                  ├──────┼───────────┼────────┼─────┼──────┼────────┤
//    │ RM_DEF1 │ RM_DEF2 │ mute │ vold │ volu │ MUTEMIC │                  │  no  │    no     │   no   │ no  │  no  │   no   │
//    ├─────────┼─────────┼──────┼──────┼──────┼─────────┤                  ├──────┼───────────┼────────┼─────┼──────┼────────┤
//    │ RM_RND  │ RM_HUEU │ G(3) │ G(2) │ G(1) │  G(d)   │                  │  no  │    no     │  rsft  │ no  │ lalt │   no   │
//    ├─────────┼─────────┼──────┼──────┼──────┼─────────┤                  ├──────┼───────────┼────────┼─────┼──────┼────────┤
//    │ LUM_CYC │ RM_NEXT │ G(6) │ G(5) │ G(4) │  G(w)   │                  │  no  │ S(A(tab)) │ A(tab) │ no  │  no  │ G(ent) │
//    └─────────┴─────────┴──────┴──────┴──────┼─────────┼────────┐   ┌─────┼──────┼───────────┴────────┴─────┴──────┴────────┘
//                                             │  mply   │ G(spc) │   │     │ lock │
//                                             └─────────┴────────┘   └─────┴──────┘
[WIN] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                           _______ , _______      , _______   , _______ , _______ , _______  ,
  RM_DEF1 , RM_DEF2 , KC_MUTE , KC_VOLD , KC_VOLU , MUTEMIC ,                           XXXXXXX , XXXXXXX      , XXXXXXX   , XXXXXXX , XXXXXXX , XXXXXXX  ,
  RM_RND  , RM_HUEU , G(KC_3) , G(KC_2) , G(KC_1) , G(KC_D) ,                           XXXXXXX , XXXXXXX      , KC_RSFT   , XXXXXXX , KC_LALT , XXXXXXX  ,
  LUM_CYC , RM_NEXT , G(KC_6) , G(KC_5) , G(KC_4) , G(KC_W) ,                           XXXXXXX , S(A(KC_TAB)) , A(KC_TAB) , XXXXXXX , XXXXXXX , G(KC_ENT),
                                                    KC_MPLY , G(KC_SPC) ,     _______ , QK_LLCK
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌──────┬────┬──────┬──────┬──────┬────────┐
//    │     │     │     │     │     │     │             │  no  │ no │  no  │  no  │  no  │   no   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├──────┼────┼──────┼──────┼──────┼────────┤
//    │ no  │ f12 │ f9  │ f8  │ f7  │ no  │             │  no  │ no │  no  │  no  │  no  │   no   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├──────┼────┼──────┼──────┼──────┼────────┤
//    │ no  │ f10 │ f3  │ f2  │ f1  │ no  │             │  no  │ no │ rsft │ rctl │ lalt │   no   │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤             ├──────┼────┼──────┼──────┼──────┼────────┤
//    │ no  │ f11 │ f6  │ f5  │ f4  │ no  │             │  no  │ no │  no  │  no  │ rgui │ QK_RBT │
//    └─────┴─────┴─────┴─────┴─────┼─────┼────┐   ┌────┼──────┼────┴──────┴──────┴──────┴────────┘
//                                  │ no  │ no │   │ no │ lock │
//                                  └─────┴────┘   └────┴──────┘
[FUN] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , KC_F12  , KC_F9   , KC_F8   , KC_F7   , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , KC_F10  , KC_F3   , KC_F2   , KC_F1   , XXXXXXX ,                         XXXXXXX , XXXXXXX , KC_RSFT , KC_RCTL , KC_LALT , XXXXXXX,
  XXXXXXX , KC_F11  , KC_F6   , KC_F5   , KC_F4   , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RGUI , QK_RBT ,
                                                    XXXXXXX , XXXXXXX ,     XXXXXXX , QK_LLCK
),

//    ┌─────────┬──────┬───────┬────────┬─────────┬──────────┐                       ┌────────┬─────────┬───────┬─────────┬─────────┬─────────┐
//    │         │      │       │        │         │          │                       │        │         │       │         │         │ AC_TOGG │
//    ├─────────┼──────┼───────┼────────┼─────────┼──────────┤                       ├────────┼─────────┼───────┼─────────┼─────────┼─────────┤
//    │         │  no  │  no   │   no   │ JIGGLE  │    no    │                       │ OM_W_U │ OM_BTN1 │ OM_U  │ OM_BTN2 │ SRCHSEL │         │
//    ├─────────┼──────┼───────┼────────┼─────────┼──────────┤                       ├────────┼─────────┼───────┼─────────┼─────────┼─────────┤
//    │ OM_SLOW │ lalt │ lctl  │  lsft  │ SELLINE │    no    │                       │ OM_W_D │  OM_L   │ OM_D  │  OM_R   │ OM_SLOW │         │
//    ├─────────┼──────┼───────┼────────┼─────────┼──────────┤                       ├────────┼─────────┼───────┼─────────┼─────────┼─────────┤
//    │         │ lgui │ PASTE │ SELALL │  COPY   │   CUT    │                       │  O_ID  │ O_EMAIL │ O_SEC │ UC_PREV │ UC_NEXT │         │
//    └─────────┴──────┴───────┴────────┴─────────┼──────────┼─────────┐   ┌─────────┼────────┼─────────┴───────┴─────────┴─────────┴─────────┘
//                                                │ www_back │ OM_BTN1 │   │ OM_BTN1 │  lock  │
//                                                └──────────┴─────────┘   └─────────┴────────┘
[EXT] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______ , AC_TOGG,
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , JIGGLE  , XXXXXXX ,                         OM_W_U  , OM_BTN1 , OM_U    , OM_BTN2 , SRCHSEL , _______,
  OM_SLOW , KC_LALT , KC_LCTL , KC_LSFT , SELLINE , XXXXXXX ,                         OM_W_D  , OM_L    , OM_D    , OM_R    , OM_SLOW , _______,
  _______ , KC_LGUI , PASTE   , SELALL  , COPY    , CUT     ,                         O_ID    , O_EMAIL , O_SEC   , UC_PREV , UC_NEXT , _______,
                                                    KC_WBAK , OM_BTN1 ,     OM_BTN1 , QK_LLCK
)
};
// clang-format on

///////////////////////////////////////////////////////////////////////////////
// Combos (https://docs.qmk.fm/features/combo)
///////////////////////////////////////////////////////////////////////////////
const uint16_t PROGMEM j_comm_combo[]    = {KC_J, KC_COMM, COMBO_END};
const uint16_t PROGMEM j_k_combo[]       = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM k_g_combo[]       = {KC_K, HRM_G, COMBO_END};
const uint16_t PROGMEM h_quot_combo[]    = {HRM_H, HRM_QUO, COMBO_END};
const uint16_t PROGMEM h_comm_combo[]    = {HRM_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM quot_comm_combo[] = {HRM_QUO, KC_COMM, COMBO_END};
const uint16_t PROGMEM h_dot_combo[]     = {HRM_H, HRM_DOT, COMBO_END};
const uint16_t PROGMEM dot_quot_combo[]  = {HRM_DOT, HRM_QUO, COMBO_END};
const uint16_t PROGMEM comm_dot_combo[]  = {KC_COMM, HRM_DOT, COMBO_END};

const uint16_t PROGMEM f_n_combo[] = {KC_F, HRM_N, COMBO_END};
const uint16_t PROGMEM y_d_combo[] = {KC_Y, HRM_D, COMBO_END};
const uint16_t PROGMEM c_p_combo[] = {KC_C, KC_P, COMBO_END};

const uint16_t PROGMEM plus_rabke_combo[] = {KC_PLUS, KC_RABK, COMBO_END};
const uint16_t PROGMEM rbrc_rabk_combo[]  = {KC_RBRC, KC_RABK, COMBO_END};
const uint16_t PROGMEM rabk_dlr_combo[]   = {KC_RABK, KC_DLR, COMBO_END};
const uint16_t PROGMEM rcb_rprn_combo[]   = {KC_RCBR, KC_RPRN, COMBO_END};
const uint16_t PROGMEM ampr_plus_combo[]  = {KC_AMPR, KC_PLUS, COMBO_END};
const uint16_t PROGMEM pipe_astr_combo[]  = {KC_PIPE, KC_ASTR, COMBO_END};
const uint16_t PROGMEM eq_lprn_combo[]    = {KC_EQL, KC_LPRN, COMBO_END};
const uint16_t PROGMEM astr_exlm_combo[]  = {KC_ASTR, KC_EXLM, COMBO_END};
const uint16_t PROGMEM dlr_rbrc_combo[]   = {KC_DLR, KC_RBRC, COMBO_END};

const uint16_t PROGMEM paste_selall_combo[] = {PASTE, SELALL, COMBO_END};

combo_t key_combos[] = {
    COMBO(j_comm_combo, CW_TOGG), // J and , => activate Caps Word.
    COMBO(j_k_combo, KC_ESC),     // J and K => esc
    COMBO(k_g_combo, KC_ENT),     // J, K and G => enter
    COMBO(f_n_combo, OSL(FUN)),   // F and N => FUN layer

    COMBO(y_d_combo, DM_REC1), // y and d => Start recording a macro
    COMBO(c_p_combo, DM_PLY1), // c and p => Play the recorded mocro

    COMBO(paste_selall_combo, PASTE_ENTER), // PASTE and SELALL => PASTE + enter

    // Symbols
    COMBO(rbrc_rabk_combo, SYM_ARROW),             // ] and > => ->
    COMBO(plus_rabke_combo, SYM_FAT_ARROW),        // + and > => =>
    COMBO(rabk_dlr_combo, SYM_POUND_SIGN),         // > and $ => £
    COMBO(rcb_rprn_combo, SYM_RPRN_AND_NEW_BLOCK), // } and ) => end ) {<cursor>}
    COMBO(ampr_plus_combo, SYM_DBLAMPR),           // & and + => &&<space>
    COMBO(pipe_astr_combo, SYM_DBLPIPE),           // | and * => ||<space>
    COMBO(eq_lprn_combo, SYM_GOASS),               // = and ( => :=
    COMBO(dlr_rbrc_combo, SYM_TEMPLATE_STRING),    // $ and ] => ${<cursor>}
    COMBO(astr_exlm_combo, SYM_MULTILINE_COMMENT), // * and ! => /* <cursor> *\/

#ifdef COMMUNITY_MODULE_XCASE_ENABLE

    COMBO(h_quot_combo, XC_TITLECASE),    // h and ' => activate Title Case
    COMBO(h_comm_combo, XC_CAMELCASE),    // h and , => activate camelCase
    COMBO(h_dot_combo, XC_PASCALCASE),    // h and . => activate PascalCase
    COMBO(comm_dot_combo, XC_SNAKECASE),  // , and . => activate snake_case
    COMBO(quot_comm_combo, XC_KEBABCASE), // , and ' => activate kebab-case
    COMBO(dot_quot_combo, XC_PATHCASE),   // . and ' => activate path/case

#endif // COMMUNITY_MODULE_XCASE_ENABLE
};

///////////////////////////////////////////////////////////////////////////////
// Custom shift keys (https://getreuer.info/posts/keyboards/custom-shift-keys)
///////////////////////////////////////////////////////////////////////////////
#ifdef COMMUNITY_MODULE_CUSTOM_SHIFT_KEYS_ENABLE
const custom_shift_key_t custom_shift_keys[] = {
    {HRM_DOT, KC_QUES}, // . -> ?
    {KC_COMM, KC_EXLM}, // , -> !
    {KC_MINS, KC_SCLN}, // - -> ;
    {KC_SLSH, KC_BSLS}, // / -> backslash
    {KC_MPLY, KC_MNXT},

    // RGB Matrix
    {RM_NEXT, RM_PREV},
    {RM_HUEU, RM_HUED},
};
#endif // COMMUNITY_MODULE_CUSTOM_SHIFT_KEYS_ENABLE

///////////////////////////////////////////////////////////////////////////////
// Autocorrect (https://docs.qmk.fm/features/autocorrect)
///////////////////////////////////////////////////////////////////////////////
#ifdef AUTOCORRECT_ENABLE
bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    for (uint8_t i = 0; i < backspaces; ++i) {
        tap_code(KC_BSPC);
    }
    send_string_with_delay_P(str, TAP_CODE_DELAY);
    return false;
}
#endif // AUTOCORRECT_ENABLE

///////////////////////////////////////////////////////////////////////////////
// Tap-hold configuration (https://docs.qmk.fm/tap_hold)
///////////////////////////////////////////////////////////////////////////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRM_S:
        case HRM_I:
            return TAPPING_TERM + 45;

        case HRM_R:
        case HRM_E:
            return TAPPING_TERM - 20;

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
        case HRM_E:
            return QUICK_TAP_TERM; // Enable key repeating.
        default:
            return 0; // Otherwise, force hold and disable key repeating.
    }
}

#ifdef CHORDAL_HOLD
// Callback for Chordal Hold (https://github.com/qmk/qmk_firmware/pull/24560)
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    switch (tap_hold_keycode) {
        case HRM_D:
            if (other_keycode == KC_M || other_keycode == KC_L || other_keycode == KC_Y || other_keycode == KC_K || other_keycode == KC_J || other_keycode == KC_V) {
                return true;
            }
            break;

        case HRM_N:
            if (other_keycode == QK_REP) {
                return true;
            }
            break;

        case HRM_DOT:
            if (other_keycode == HRM_H || other_keycode == KC_COMM) {
                return true;
            }
            break;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif // CHORDAL_HOLD

///////////////////////////////////////////////////////////////////////////////
// Sentence case (https://getreuer.info/posts/keyboards/sentence-case)
///////////////////////////////////////////////////////////////////////////////
#ifdef COMMUNITY_MODULE_SENTENCE_CASE_ENABLE
char sentence_case_press_user(uint16_t keycode, keyrecord_t *record, uint8_t mods) {
    if ((mods & ~(MOD_MASK_SHIFT | MOD_BIT_RALT)) == 0) {
        const bool shifted = mods & MOD_MASK_SHIFT;
        switch (keycode) {
            case KC_A ... KC_Z:
            case M_THE:
            case M_ION:
            case M_MENT:
            case M_TMENT:
                return 'a'; // Letter key.

            case KC_DOT: // Both . and Shift . (?) punctuate sentence endings.
            case KC_EXLM:
            case KC_QUES:
                return '.';

            case KC_COMM:
                return shifted ? '.' : '#';

            case KC_2 ... KC_0:       // 2 3 4 5 6 7 8 9 0
            case KC_AT ... KC_RPRN:   // @ # $ % ^ & * ( )
            case KC_MINS ... KC_SCLN: // - = [ ] backslash ;
            case KC_UNDS ... KC_COLN: // _ + { } | :
            case KC_GRV:
                return '#'; // Symbol key.

            case KC_SPC:
                return ' '; // Space key.

            case KC_QUOT:
            case KC_DQUO:
                return '\''; // Quote key.
        }
    }

    // Otherwise clear Sentence Case to initial state.
    sentence_case_clear();
    return '\0';
}
#endif // COMMUNITY_MODULE_SENTENCE_CASE_ENABLE

///////////////////////////////////////////////////////////////////////////////
// XCase
///////////////////////////////////////////////////////////////////////////////
#ifdef COMMUNITY_MODULE_XCASE_ENABLE
bool terminate_case_modes_user(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case KC_QUOT:
        case M_ION:
        case M_MENT:
        case M_QUEN:
        case M_THE:
        case M_TMENT:
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
#endif // COMMUNITY_MODULE_XCASE_ENABLE

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
//     ( *   -> (<cursor>)
//     [ *   -> [<cursor>]
//     < *   -> <<cursor>>
//     { *   -> {<cursor>}
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
            case KC_DOT:
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
            case KC_EXLM:
                return M_EQEQ; // ! -> ==

            case KC_AT:
                return USRNAME; // @ -> <username>

            case KC_DQUO:
                return M_DOCSTR; // " -> ""<cursor>"""
            case HRM_QUO:
                if ((mods & MOD_MASK_SHIFT) != 0) {
                    return M_DOCSTR; // " -> ""<cursor>"""
                }
                return M_NOOP;
            case KC_GRV: // ` -> ``<cursor>``` (for Markdown code)
                return M_MKGRVS;

            case KC_LBRC:
                return M_BRC; // [ -> ]
            case KC_LABK:
                return M_ABK; // < -> >
            case KC_LCBR:
                return M_CBR; // { -> }
            case KC_LPRN:
                return M_PRN; // ( -> )

            case KC_PLUS: // + -> =
            case KC_MINS: // - -> =
            case KC_ASTR: // * -> =
            case KC_PERC: // % -> =
            case KC_PIPE: // | -> =
            case KC_CIRC: // ^ -> =
            case KC_TILD: // ~ -> =
            case KC_DLR:  // $ -> =
            case KC_UNDS: // _ -> =
            case KC_COLN: // : -> =
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

#ifdef COMMUNITY_MODULE_SELECT_WORD_ENABLE
        case SELWBAK:
            return SELWORD;
        case SELWORD:
            return SELWBAK;
#endif // COMMUNITY_MODULE_SELECT_WORD_ENABLE
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

///////////////////////////////////////////////////////////////////////////////
// Custom RGB
///////////////////////////////////////////////////////////////////////////////
bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case GAME:
            rgb_matrix_set_color_all(0, 0, 0);
            rgb_matrix_set_color(0, RGB_RED);

            rgb_matrix_set_color(9, RGB_WHITE);
            rgb_matrix_set_color(14, RGB_WHITE);
            rgb_matrix_set_color(15, RGB_WHITE);
            rgb_matrix_set_color(16, RGB_WHITE);

            rgb_matrix_set_color(24, RGB_WHITE);
            rgb_matrix_set_color(25, RGB_WHITE);

            rgb_matrix_set_color(18, RGB_GREEN);
            break;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Status LEDs
///////////////////////////////////////////////////////////////////////////////
#ifdef STATUS_LED_1
// LED 1 indicates when any layer above the SYM layer is active.
layer_state_t layer_state_set_user(layer_state_t state) {
    STATUS_LED_1(get_highest_layer(layer_state) > SYM);
    return state;
}
#endif // STATUS_LED_1

#ifdef STATUS_LED_2
// LED 2 indicates when Sentence case is in primed to capitalize the next key.
void sentence_case_primed(bool primed) {
    STATUS_LED_2(primed);
}
#endif // STATUS_LED_2

#ifdef STATUS_LED_3
// LED 3 indicates when Caps word is active.
void caps_word_set_user(bool active) {
    STATUS_LED_3(active);
}
#endif // STATUS_LED_3

///////////////////////////////////////////////////////////////////////////////
// RGB Matrix Lighting (https://docs.qmk.fm/features/rgb_matrix)
///////////////////////////////////////////////////////////////////////////////
#if RGB_MATRIX_ENABLE
static void lighting_set_palette(uint8_t palette) {
#    ifdef COMMUNITY_MODULE_LUMINO_ENABLE
    if (lumino_get_value() == 0) {
        lumino_cycle_3_state();
    }
#    endif // COMMUNITY_MODULE_LUMINO_ENABLE
    rgb_matrix_sethsv_noeeprom(RGB_MATRIX_HUE_STEP * palette, 255, 255);
    rgb_matrix_enable_noeeprom();
}

static void lighting_preset(uint8_t effect, uint8_t palette) {
    rgb_matrix_mode_noeeprom(effect);
    lighting_set_palette(palette);
    rgb_matrix_set_speed_noeeprom(128);
}
#endif // RGB_MATRIX_ENABLE

///////////////////////////////////////////////////////////////////////////////
// User macro callbacks (https://docs.qmk.fm/feature_macros)
///////////////////////////////////////////////////////////////////////////////
void keyboard_post_init_user(void) {
#if RGB_MATRIX_ENABLE
    lighting_preset(RGB_MATRIX_CUSTOM_PALETTEFX_FLOW, PALETTEFX_SYNTHWAVE);
#endif // RGB_MATRIX_ENABLE
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Track whether the left home ring and index keys are held, ignoring layer.
    static bool left_home_ring_held  = false;
    static bool left_home_index_held = false;
    if (record->event.key.row == LEFT_HOME_ROW) {
        switch (record->event.key.col) {
            case LEFT_HOME_RING_COL:
                left_home_ring_held = record->event.pressed;
                break;
            case LEFT_HOME_INDEX_COL:
                left_home_index_held = record->event.pressed;
                break;
        }

        // NAV stays on while layer locked or while either ring or index is held.
        if (!(is_layer_locked(NAV) || left_home_ring_held || left_home_index_held)) {
            layer_off(NAV);
        }
    }

    // Logic for Alt mod when using alt-tabbing keys.
    if ((keycode == HRM_DOT || keycode == HRM_D) && record->tap.count == 0 && !record->event.pressed) {
        unregister_mods(MOD_BIT_LALT);
    } else if (record->event.pressed && (keycode == S(A(KC_TAB)) || keycode == A(KC_TAB))) {
        register_mods(MOD_BIT_LALT);
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = (mods | get_weak_mods()
#ifndef NO_ACTION_ONESHOT
                              | get_oneshot_mods()
#endif // NO_ACTION_ONESHOT
    );
    const uint8_t shift_mods = all_mods & MOD_MASK_SHIFT;
    const bool    alt        = all_mods & MOD_BIT_LALT;
    const uint8_t layer      = read_source_layers_cache(record->event.key);

    if (layer == SYM && record->event.pressed) {
        clear_weak_mods();
        send_keyboard_report();
    }

    // If alt repeating key A, E, I, O, U, Y with no mods other than Shift, set
    // the last key to KC_N. Above, alternate repeat of KC_N is defined to be
    // again KC_N. This way, either tapping alt repeat and then repeat (or
    // equivalently double tapping alt repeat) is useful to type certain patterns
    // without SFBs:
    //
    //   D <altrep> <rep> -> DYN (as in "dynamic")
    //   O <altrep> <rep> -> OAN (as in "loan")
    if (get_repeat_key_count() < 0 && (all_mods & ~MOD_MASK_SHIFT) == 0 && (keycode == KC_A || keycode == KC_E || keycode == KC_I || keycode == KC_O || keycode == KC_U || keycode == KC_Y)) {
        set_last_keycode(KC_N);
        set_last_mods(0);
    }

    switch (keycode) {
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

            // Behavior:
            //  * Unmodified:       backspace
            //  * With Shift:       delete
            //  * With both shifts: shift + delete
        case KC_BSPC: {
            static uint16_t registered_key = KC_NO;
            if (record->event.pressed) { // On key press.
                const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
                uint8_t shift_mods = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;
#else
                uint8_t shift_mods = mods & MOD_MASK_SHIFT;
#endif                            // NO_ACTION_ONESHOT
                if (shift_mods) { // At least one shift key is held.
                    registered_key = KC_DEL;
                    // If one shift is held, clear it from the mods. But if both
                    // shifts are held, leave as is to send Shift + Del.
                    if (shift_mods != MOD_MASK_SHIFT) {
#ifndef NO_ACTION_ONESHOT
                        del_oneshot_mods(MOD_MASK_SHIFT);
#endif // NO_ACTION_ONESHOT
                        unregister_mods(MOD_MASK_SHIFT);
                    }
                } else {
                    registered_key = KC_BSPC;
                }

                register_code(registered_key);
                set_mods(mods);
            } else { // On key release.
                unregister_code(registered_key);
            }
        }
            return false;

        // Hold behavior: switches to EXT layer.
        // Tap behavior:
        //  * Unmodified:       :
        //  * With Shift:       ;
        case EXT_COL:
            if (record->tap.count) {
                if (record->event.pressed) {
                    if (shift_mods) {
                        del_weak_mods(MOD_MASK_SHIFT);
                        unregister_mods(MOD_MASK_SHIFT);
                        tap_code_delay(KC_SCLN, TAP_CODE_DELAY);
                        set_mods(mods);
                    } else {
                        tap_code16_delay(KC_COLN, TAP_CODE_DELAY);
                    }
                }
                return false;
            }
            return true;

        case HRM_T:
            if (!record->tap.count) {
                if (record->event.pressed) {
                    if ((mods & MOD_BIT_LSHIFT) != 0) {
                        register_mods(MOD_BIT_LCTRL);
                        layer_on(NAV);
                    } else {
                        layer_on(SYM);
                    }
                } else {
                    unregister_mods(MOD_BIT_LCTRL);
                    layer_off(SYM);
                }
                return false;
            }
            return true;

        case HRM_D: // NAV switch.
            if (!record->tap.count) {
                if (record->event.pressed) {
                    layer_on(NAV);
                }
                return false;
            }
            return true;
    }

    if (record->event.pressed) {
#ifdef ENABLE_MOUSE_JIGGLER
        static deferred_token token  = INVALID_DEFERRED_TOKEN;
        static report_mouse_t report = {0};
        if (token) {
            // If jiggler is currently running, stop when any key is pressed.
            cancel_deferred_exec(token);
            token  = INVALID_DEFERRED_TOKEN;
            report = (report_mouse_t){}; // Clear the mouse.
            host_mouse_send(&report);
        } else if (keycode == JIGGLE) {
            uint32_t jiggler_callback(uint32_t trigger_time, void *cb_arg) {
                // Deltas to move in a circle of radius 20 pixels over 32 frames.
                static const int8_t deltas[32] = {0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
                static uint8_t      phase      = 0;
                // Get x delta from table and y delta by rotating a quarter cycle.
                report.x = deltas[phase];
                report.y = deltas[(phase + 8) & 31];
                phase    = (phase + 1) & 31;
                host_mouse_send(&report);
                return 16; // Call the callback every 16 ms.
            }

            token = defer_exec(1, jiggler_callback, NULL); // Schedule callback.
        }
#endif

        switch (keycode) {
            case UPDIR:
                SEND_STRING_DELAY("../", TAP_CODE_DELAY);
                return false;

            case SRCHSEL: // Searches the current selection in a new tab.
                // Mac users, change LCTL to LGUI.
                SEND_STRING_DELAY(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER), TAP_CODE_DELAY);
                return false;

            case USRNAME:
                add_oneshot_mods(shift_mods);
                clear_weak_mods();
                MAGIC_STRING("omareloui", KC_AT);
                return false;

            case O_ID:
                add_oneshot_mods(shift_mods);
                clear_weak_mods();
                send_string_with_delay_P("VPYH9010", TAP_CODE_DELAY);
                return false;
            case O_EMAIL:
                add_oneshot_mods(shift_mods);
                clear_weak_mods();
                send_string_with_delay_P("omar.eloui@orange.com", TAP_CODE_DELAY);
                return false;
            case O_CD_EMAIL:
                add_oneshot_mods(shift_mods);
                clear_weak_mods();
                send_string_with_delay_P("omar.eloui@orangecyberdefense.com", TAP_CODE_DELAY);
                return false;
            case O_SEC:
                add_oneshot_mods(shift_mods);
                clear_weak_mods();
                send_string_with_delay_P("oeloui.SEC", TAP_CODE_DELAY);
                return false;

            case ARROW:                                                   // Unicode arrows -> => <-> <=> through Shift and Alt.
                send_unicode_string(alt ? (shift_mods ? "\xe2\x87\x94"    // <=>
                                                      : "\xe2\x86\x94")   // <->
                                        : (shift_mods ? "\xe2\x87\x92"    // =>
                                                      : "\xe2\x86\x92")); // ->
                return false;

            case PASTE_ENTER:
                SEND_STRING(SS_LCTL("v") SS_TAP(X_ENTER));
                break;

            // Symbols
            case SYM_ARROW:
                SEND_STRING("->");
                break;
            case SYM_FAT_ARROW:
                SEND_STRING("=>");
                break;
            case SYM_GOASS:
                SEND_STRING(":=");
                break;
            case SYM_RPRN_AND_NEW_BLOCK:
                SEND_STRING(SS_TAP(X_END) ") {}" SS_TAP(X_LEFT));
                break;
            case SYM_TEMPLATE_STRING:
                SEND_STRING("${}" SS_TAP(X_LEFT));
                break;
            case SYM_MULTILINE_COMMENT:
                SEND_STRING("/*  */" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
                break;
            case SYM_DBLAMPR:
                SEND_STRING("&&");
                break;
            case SYM_DBLPIPE:
                SEND_STRING("||");
                break;
            case SYM_POUND_SIGN:
                send_unicode_string("£");
                break;

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
            case M_ABK:
                SEND_STRING(/*<*/ ">");
                break;
            case M_BRC:
                SEND_STRING(/*[*/ "]");
                break;
            case M_CBR:
                SEND_STRING(/*{*/ "}");
                break;
            case M_PRN:
                SEND_STRING(/*(*/ ")");
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

#ifdef COMMUNITY_MODULE_LUMINO_ENABLE
            case G(KC_L):
                lumino_sleep_soon();
                return true;

            case LUM_CYC:
                lumino_cycle_3_state();
                return false;
#endif // COMMUNITY_MODULE_LUMINO_ENABLE

#if RGB_MATRIX_ENABLE
            case RM_RND: {
                uint8_t h = (UINT16_C(17099) * timer_read()) >> 8;
                lighting_preset(RGB_MATRIX_CUSTOM_PALETTEFX_FLOW, h);
                return false;
            }

            case RM_DEF1:
                lighting_preset(RGB_MATRIX_CUSTOM_PALETTEFX_FLOW, PALETTEFX_SYNTHWAVE);
                return false;

            case RM_DEF2:
                lighting_preset(RGB_MATRIX_CUSTOM_PALETTEFX_RIPPLE, PALETTEFX_WATERMELON);
                return false;
#endif // RGB_MATRIX_ENABLE
        }
    }

    return true;
};
