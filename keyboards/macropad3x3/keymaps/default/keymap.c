#include QMK_KEYBOARD_H

#define _BASE 0
#define _FN1 1
#define _FN2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_3x3(
    KC_P7,  KC_P8,  KC_P9, \
    KC_P4,  KC_P5,  KC_P6, \
    KC_1,  KC_P2,  KC_P3 \
  ),
  [_FN2] = LAYOUT_ortho_3x3(
    _______,  _______,  _______,  \
    _______,  _______,  _______,  \
    _______,  _______,  _______  \
  )
};
