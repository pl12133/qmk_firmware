// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later
#include "vimmode.h"

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
    _ADJUST,
    _VIM,
    _WORKMAN
};

#define RAISE MO(_RAISE)
#define LOWER LT(_LOWER, KC_ESC)
#define WKMAN TG(_WORKMAN)

// Easy Vim-like movement
#define VIM_E LALT(KC_RGHT)   // e, end of word
#define VIM_B LALT(KC_LEFT)   // b, back word
#define VIM_BOL LGUI(KC_LEFT) // 0, jump to beginning of line
#define VIM_EOL LGUI(KC_RGHT) // $, jump to end of line

// Spectacle keybindings
#define SPC_RGH LCTL(LALT(LGUI(KC_RGHT)))
#define SPC_LFT LCTL(LALT(LGUI(KC_LEFT)))
// Caps Lock on Double Shift
#define TD_F1 TD(_TD_F1)
#define TD_F2 TD(_TD_F2)
#define TD_F3 TD(_TD_F3)
#define TD_F4 TD(_TD_F4)
#define TD_F5 TD(_TD_F5)
#define TD_F6 TD(_TD_F6)
#define TD_F7 TD(_TD_F7)
#define TD_F8 TD(_TD_F8)
#define TD_F9 TD(_TD_F9)
#define TD_F10 TD(_TD_F10)
#define TD_F11 TD(_TD_F11)
#define TD_F12 TD(_TD_F12)

// Mod-tap space / shift (unused - i didnt like it much)
#define MT_SPC LSFT_T(KC_SPC)

// Tap Dance action codes
enum {
    _TD_F1,
    _TD_F2,
    _TD_F3,
    _TD_F4,
    _TD_F5,
    _TD_F6,
    _TD_F7,
    _TD_F8,
    _TD_F9,
    _TD_F10,
    _TD_F11,
    _TD_F12,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [_TD_F1] = ACTION_TAP_DANCE_DOUBLE(KC_BRID, KC_F1),
    [_TD_F2] = ACTION_TAP_DANCE_DOUBLE(KC_BRIU, KC_F2),
    [_TD_F3] = ACTION_TAP_DANCE_DOUBLE(_______, KC_F3),
    [_TD_F4] = ACTION_TAP_DANCE_DOUBLE(_______, KC_F4),
    [_TD_F5] = ACTION_TAP_DANCE_DOUBLE(BL_DEC, KC_F5),
    [_TD_F6] = ACTION_TAP_DANCE_DOUBLE(BL_INC, KC_F6),
    [_TD_F7] = ACTION_TAP_DANCE_DOUBLE(KC_MPRV, KC_F7),
    [_TD_F8] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_F8),
    [_TD_F9] = ACTION_TAP_DANCE_DOUBLE(KC_MNXT, KC_F9),
    [_TD_F10] = ACTION_TAP_DANCE_DOUBLE(KC_MUTE, KC_F10),
    [_TD_F11] = ACTION_TAP_DANCE_DOUBLE(KC_VOLD, KC_F11),
    [_TD_F12] = ACTION_TAP_DANCE_DOUBLE(KC_VOLU, KC_F12),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool vim_handled = handle_vim_mode(keycode, record, _VIM);
  if (vim_handled)
    return false;

  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | `    |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |ESC   |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LALT,    KC_LGUI, LOWER, KC_SPC,  KC_ENT,   RAISE,   KC_BSPC, KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|   (   |    |    )  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   +  |   [  |   ]  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  TD_F1,   TD_F2,   TD_F3,   TD_F4,   TD_F5,   TD_F6,                     TD_F7,   TD_F8,   TD_F9,   TD_F10,  TD_F11,  TD_F12,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, KC_PLUS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | WKMAN|      |      |      | EOL  |      |                    |      |      |      |      |  BOL |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |RWord | Ins  |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| Left | Down |  Up  |Right |  XXX |  XXX |
 * |------+------+------+------+------+------|   (   |    |   )   |------+------+------+------+------+------|
 * |      |SPC_LF|SPC_RI|      |      |LWord |-------|    |-------|   +  |   -  |   =  |   >  |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP|Delete|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  WKMAN,   _______, _______, _______, VIM_EOL, _______,                    _______, _______, _______, _______, VIM_BOL, _______,
  _______, _______, _______, VIM_E,   KC_INS,  _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
  _______, SPC_LFT, SPC_RGH, _______, _______, VIM_B,    KC_LPRN, KC_RPRN, KC_PLUS, KC_MINS, KC_EQL,  KC_RABK, KC_BSLS, _______,
                             _______, _______, VIM_ESC,  _______, _______, _______, _______, KC_DEL
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* VIM
 * Layer handled entirely by process_record_user function implemented in vimmode.c
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_VIM] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LALT,    KC_LGUI, LOWER, KC_SPC,  KC_ENT,   RAISE,   KC_BSPC, KC_RGUI
),

/* Workman
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | `    |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   ;  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   M  |   C  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |WKMAN |BackSP| RGUI |
 *                   |      |      |ESC   |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_WORKMAN] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  KC_TAB,   KC_Q,   KC_D,    KC_R,    KC_W,    KC_B,                     KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_H,    KC_T,    KC_G,                     KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_M,    KC_C,    KC_V, KC_LBRC,  KC_RBRC,  KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LALT,    KC_LGUI, LOWER, KC_SPC,  KC_ENT,   WKMAN,   KC_BSPC, KC_RGUI
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
