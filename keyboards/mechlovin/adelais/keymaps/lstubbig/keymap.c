/* Copyright 2020 Team Mechlovin
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
#include QMK_KEYBOARD_H

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define SHFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_alice(
     KC_MAIL, F(0),       KC_1, KC_2,    KC_3, KC_4,   KC_5, KC_6,            KC_7, KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
     KC_CALC, KC_TAB,     KC_Q, KC_W,    KC_E, KC_R,   KC_T,                  KC_Y, KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLASH,
     KC_LWIN, KC_ESC,     KC_A, KC_S,    KC_D, KC_F,   KC_G,                  KC_H, KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
              KC_LSFT,    KC_Z, KC_X,    KC_C, KC_V,   KC_B,                  KC_B, KC_N,   KC_M,   KC_COMM,  KC_DOT,  KC_SLASH,KC_RSFT,  MO(1), 
              KC_LCTL,    KC_LALT,       KC_ENTER,     MO(2),                 LT(3,KC_SPC),          KC_RALT,                       KC_RCTL ),
    [1] = LAYOUT_alice(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS,                                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
     KC_TRNS, KC_CAPS,  RGB_MOD, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, RGB_MODE_SWIRL,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, RGB_MODE_XMAS, RGB_MODE_GRADIENT, RGB_MODE_RGBTEST,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                                  KC_TRNS,          KC_TRNS,                            KC_TRNS ),
    [2] = LAYOUT_alice(
     KC_TRNS, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,           KC_F7,        KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,                  LALT(KC_F4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,                 KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,         KC_TRNS,          KC_TRNS,                            KC_PSCREEN ),
    [3] = LAYOUT_alice(
     KC_TRNS, KC_GRV,  KC_F1,   KC_F2,      KC_F3,   KC_F4,   RALT(KC_5),   KC_F6,           KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_DEL,
     KC_TRNS, KC_TRNS, RALT(KC_Q), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               RALT(KC_Y), KC_HOME, KC_END,  KC_TRNS, RALT(KC_P),KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_DEL,  KC_TRNS, RALT(KC_S), KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,  KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_MUTE, KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU,   KC_MNXT, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS,             KC_TRNS,          KC_TRNS,                  KC_TRNS,          KC_TRNS,                              KC_PSCREEN ),
};


// custom shift escape functions
// keycode: F(0)
enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if ((get_mods()&CTRL_MASK) && (get_mods()&SHFT_MASK)) {
          add_key(KC_ESC);
          send_keyboard_report();
        }
        else if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if ((get_mods()&CTRL_MASK) && (get_mods()&SHFT_MASK)) {
          del_key(KC_ESC);
          send_keyboard_report();
        }
        else if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}