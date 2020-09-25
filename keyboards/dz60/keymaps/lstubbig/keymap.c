#include QMK_KEYBOARD_H

// Shift ESC: Normally ESC, shift+esc: ~, Fn+esc: `, Alt also causes ~ to enable Alt+~ to switch windows in Linux
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
// used to enable ctrl+shift+esc shortcut in Windows
#define SHFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))

#define COMPOSE KC_SCROLLLOCK
#define _QWERTY 0
#define _GAME 1
#define _SET 2
#define _NAV 3

enum custom_keycodes {
  ATOM_RUN,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ATOM_RUN:
      if (record->event.pressed) {
        // when keycode ATOM_RUN is pressed
				// In Atom: Save file, focus open terminal and run last command
        SEND_STRING(SS_LCTRL("s")SS_LALT("t")SS_TAP(X_UP)SS_TAP(X_ENTER));
      } else {
        // when keycode QMKBEST is released
      }
      break;

  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
		F(0), 		KC_1, 	KC_2, 	KC_3, 	KC_4, 		KC_5, 	KC_6, 		KC_7,  	KC_8,  KC_9, 		KC_0, 		KC_MINS, KC_EQL, 	KC_NO, 		KC_BSPC,
		KC_TAB, 	KC_Q, 	KC_W, 	KC_E, 	KC_R, 		KC_T, 	KC_Y, 		KC_U,  	KC_I,  KC_O,  		KC_P, 		KC_LBRC, KC_RBRC, 	KC_BSLS,
		KC_ESC, 	KC_A, 	KC_S, 	KC_D, 	KC_F, 		KC_G, 	KC_H, 		KC_J,  	KC_K,  KC_L, 		KC_SCLN, 	KC_QUOT, KC_ENT,
		KC_LSFT, 	KC_NO, 	KC_Z, 	KC_X, 	KC_C, 		KC_V, 	KC_B, 		KC_N,  	KC_M,  KC_COMM,		KC_DOT, 	KC_SLSH, KC_RSFT, 	COMPOSE,
		KC_LCTL, 	KC_LGUI,KC_LALT,KC_ENT, TT(_NAV),	KC_SPC, KC_RALT,	KC_APP, KC_NO, MO(_SET), 	KC_RCTL),

  [_GAME] = LAYOUT(
		F(0), 		KC_1, 	KC_2, 	KC_3, 	KC_4, 		KC_5, 	KC_6, 		KC_7,  	KC_8,  KC_9, 		KC_0, 		KC_MINS, KC_EQL, 	KC_NO, 		KC_BSPC,
		KC_TAB, 	KC_Q, 	KC_W, 	KC_E, 	KC_R, 		KC_T, 	KC_Y, 		KC_U,  	KC_I,  KC_O,  		KC_P, 		KC_LBRC, KC_RBRC, 	KC_BSLS,
		KC_BSPC, 	KC_A, 	KC_S, 	KC_D, 	KC_F, 		KC_G, 	KC_H, 		KC_J,  	KC_K,  KC_L, 		KC_SCLN, 	KC_QUOT, KC_ENT,
		KC_LSFT, 	KC_NO, 	KC_Z, 	KC_X, 	KC_C, 		KC_V, 	KC_B, 		KC_N,  	KC_M,  KC_COMM,		KC_DOT, 	KC_SLSH, KC_RSFT, 	COMPOSE,
		KC_LCTL, 	KC_LGUI,KC_LALT,KC_SPC, TT(_NAV),	KC_SPC, KC_RALT,	KC_APP, KC_NO, MO(_SET), 	KC_RCTL),

	[_SET] = LAYOUT(
		KC_GRV,  KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_DEL,
		KC_TRNS, RGB_TOG,   RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
		KC_CAPS, DF(_GAME), DF(_QWERTY), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[_NAV] = LAYOUT(
		KC_GRV,		KC_F1,  	KC_F2,  	KC_F3,   	KC_F4,   			KC_F5,						KC_F6,	 	KC_F7,   KC_F8,   	KC_F9,		KC_F10,  	KC_F11,  	KC_F12,  KC_TRNS, KC_DEL,
		KC_TRNS,	KC_HOME,	KC_UP,		KC_END,		LALT(KC_R), 	LALT(KC_T), 			ATOM_RUN, KC_HOME, KC_END,		KC_PGUP,	KC_PGDOWN, 	KC_INS, 	KC_TRNS, KC_TRNS,
		KC_DEL,		KC_LEFT,	KC_DOWN,	KC_RIGHT, KC_TRNS, 			KC_TRNS, 					KC_TRNS, 	KC_LEFT, KC_DOWN, 	KC_UP,		KC_RIGHT, 	KC_APP, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS, 	KC_TRNS, 			LCTL(LALT(KC_V)),	KC_MUTE, 	KC_MPRV, KC_VOLD,		KC_VOLU,	KC_MNXT, 	KC_MPLY, 	KC_TRNS, 	KC_TRNS,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS, 	KC_TRNS, 			KC_TRNS, 					KC_TRNS, 	KC_TRNS, KC_TRNS, 	KC_TRNS,	KC_PSCREEN),
};

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
