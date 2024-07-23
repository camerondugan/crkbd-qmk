/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum my_custom_keys {
    ST_TOGG = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
CTL_T(KC_ESC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,RSFT_T(KC_ENT),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_SPC,   MO(2), KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_SPC,   MO(3), KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
MT(MOD_LCTL,KC_ESC),_______,_______,_______,_______,_______,                     KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_PIPE,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_SPC,     KC_SPC, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, _______, _______, _______, _______, _______,                    _______, KC_MUTE, KC_BRID, KC_BRIU, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, AS_TOGG, ST_TOGG,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,                      DM_REC1, DM_PLY1, DM_REC2, DM_PLY2, _______, DM_RSTP,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_SPC, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  )
};

// const uint16_t PROGMEM better_escape[] = {KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
// combo_t key_combos[] = {
//     COMBO(better_escape, KC_ESC),
//     COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
// };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool snapTapEnabled = false;
  static bool aHeld = false;
  static bool dHeld = false;
  switch (keycode) {
    case ST_TOGG:
      if (record->event.pressed) {
          snapTapEnabled = !snapTapEnabled;
      }
      return true;
    case KC_A:
      if (!snapTapEnabled) {
        return true;
      }
      aHeld = record->event.pressed;
      if (dHeld && aHeld) {
          unregister_code(KC_D);
      } else if (dHeld && !aHeld){
          unregister_code(KC_A);
          register_code(KC_D);
          return false; // don't send original key pressed
      }
      return true;
    case KC_D:
      if (!snapTapEnabled) {
        return true;
      }
      dHeld = record->event.pressed;
      if (aHeld && dHeld) {
          unregister_code(KC_A);
      } else if (aHeld && !dHeld){
          unregister_code(KC_D);
          register_code(KC_A);
          return false; // don't send original key pressed
      }
      return true;
    default:
      return true; // Process all other keycodes normally
  }
}
