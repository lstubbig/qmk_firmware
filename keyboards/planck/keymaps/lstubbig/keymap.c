/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  LOWER,
  RAISE,
  ADJUST,
  typeLayout
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | ESC  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;: |  '"  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,< |   .> |   /? |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL |Adjust| GUI  | ALT  |Lower | Enter| Space|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ESC,
  KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, ADJUST,	KC_LGUI, KC_LALT, LOWER,   KC_ENT,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |   !  |   7  |   8  |   9  |   *  |  +   |   *  |   [  |   ]  |   ß  |  &   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   @  |   4  |   5  |   6  |   %  |  -   |   _  |   (  |   )  |   \  |  `   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   #  |   $  |   1  |   2  |   3  |Enter |  =   |   /  |   {  |   }  |   |  |  ^   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ,  |   0  |   .  |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_TILD, 	KC_EXLM, KC_7,  KC_8, 	KC_9,    KC_ASTR, 	KC_PLUS, 	 KC_ASTR, 	KC_LBRACKET, 	KC_RBRACKET, 	 RALT(KC_S), KC_AMPR,
  KC_DEL,  	KC_AT,	 KC_4,  KC_5,   KC_6,    KC_PERC,   KC_MINUS,   KC_UNDS, 	KC_LPRN, 		  KC_RPRN, 		   KC_BSLASH, 	KC_GRV,
  KC_HASH, 	KC_DLR,  KC_1,  KC_2,   KC_3,    KC_ENT,  	KC_EQUAL,	  KC_SLSH,	KC_LCBR, 		  KC_RCBR, 		   KC_PIPE, 	KC_CIRC,
  _______, 	KC_COMM, KC_0,  KC_DOT, _______, _______, 	_______, 	  _______, 	_______, 		  _______, 		   _______, 	_______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |Mouse1|   Up |Mouse2|      |      |      | Home | End  |PgDown| PgUp | ESC  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |Insert| Left | Down |  Up  | Right| Appli|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | MAcc0|Mouse3| MAcc2|      |      | Mute | Prev |Vol - |Vol + | Next | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | Print|
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
	_______, KC_MS_BTN1,	KC_MS_UP,   	KC_MS_BTN2, 	_______,    _______,    _______, KC_HOME,	KC_END,  KC_PGDOWN, KC_PGUP, 	KC_ESC,
	_______, KC_MS_LEFT,  	KC_MS_DOWN,		KC_MS_RIGHT,	_______,   	_______,   	KC_INS , KC_LEFT, 	KC_DOWN, KC_UP,     KC_RGHT, 	KC_APPLICATION,
	_______, KC_MS_ACCEL0,	KC_MS_BTN3,		KC_MS_ACCEL2,   _______,  	_______,  	KC_MUTE, KC_MPRV, 	KC_VOLD, KC_VOLU,   KC_MNXT,	KC_MPLY,
	_______, _______, 		_______, 		_______, 		_______, 	_______, 	_______, _______, 	_______, _______,    _______, 	KC_PSCREEN
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  | F9   |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      | Home | F5   |  F4  |CtAlDe| ESC  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
   |      |      |Qwerty|Colemk|Dvorak|Plover|      | Left | Down |  Up  | Right| Appli|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Layout|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  KC_F1,   		KC_F2,   	KC_F3,   	KC_F4,   	KC_F5,   	KC_F6,   	KC_F7,   	KC_F8,   KC_F9,   	KC_F10,  		KC_F11,  			KC_F12,
  _______, 		RESET  , 	_______, 	_______, 	_______, 	_______, 	_______, 	KC_HOME, KC_F5, 	LALT(KC_F4), 	LCTL(LALT(KC_DEL)), KC_ESC,
  _______, 		_______, 	QWERTY,  	COLEMAK, 	DVORAK,  	PLOVER, 	_______, 	KC_LEFT, KC_DOWN, 	KC_UP,   		KC_RGHT, 			KC_APPLICATION,
  typeLayout,	_______,  	_______, 	_______,   	_______,  	_______,   	_______,  	_______, _______, 	_______, 		_______, 			_______
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
)


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
	  break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
	case typeLayout:
      if (record->event.pressed) {
        SEND_STRING("Lower:\n,-----------------------------------------------------------------------------------.\n|   ~   |   !  |   7  |   8  |   9  |   *  |  +   |   *  |   [  |   ]  | GerS |  &   |\n|------+------+------+------+------+-------------+------+------+------+------+------|\n| Del  |   @  |   4  |   5  |   6  |   %  |  -   |   _  |   (  |   )  |BckSlh|  `    |\n|------+------+------+------+------+------|------+------+------+------+------+------|\n|   #  |   $  |   1  |   2  |   3  |Enter |  =   |   /  |   {  |   }  |   |  |  ^    |\n|------+------+------+------+------+------+------+------+------+------+------+------|\n|      |   ,  |   0  |   .  |      |             |      |      |      |      |      |\n`-----------------------------------------------------------------------------------' \n");
        SEND_STRING("Raise:\n,-----------------------------------------------------------------------------------.\n|      |Mouse1|   Up |Mouse2|      |      |      | Home | End  |PgDown| PgUp | ESC  |\n|------+------+------+------+------+-------------+------+------+------+------+------|\n|      | Left | Down | Right|      |      |      | Left | Down |  Up  | Right| Appli| \n|------+------+------+------+------+------|------+------+------+------+------+------|\n|      | MAcc0|Mouse3| MAcc2|      |      | Mute | Prev |Vol - |Vol + | Next | Play |\n|------+------+------+------+------+------+------+------+------+------+------+------|\n|      |      |      |      |      |             |      |      |      |      | Print| \n`-----------------------------------------------------------------------------------' \n");
		SEND_STRING("Adjust:\n,-----------------------------------------------------------------------------------.\n|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  | F9   |  F10 |  F11 |  F12 |\n|------+------+------+------+------+-------------+------+------+------+------+------|\n|      | Reset|      |      |      |      |      | Home | F5   |  F4  |CtAlDe| ESC  |\n|------+------+------+------+------+------|------+------+------+------+------+------|\n|      |      |Qwerty|Colemk|Dvorak|Plover|      | Left | Down |  Up  | Right| Appli| \n|------+------+------+------+------+------|------+------+------+------+------+------|\n|      |      |      |      |      |      |      |      |      |      |      |      |\n`-----------------------------------------------------------------------------------' \n");
		return false;
	  }
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (index == 0) {
      if (clockwise) {
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      } else {
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      }
    } else {
      if (clockwise) {
        register_code(KC_VOLU);
        unregister_code(KC_VOLU);
      } else {
        register_code(KC_VOLD);
        unregister_code(KC_VOLD);
      }
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
