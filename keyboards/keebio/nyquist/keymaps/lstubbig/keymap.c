
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

// Use to enable tilde symbol for shifted ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
// define the compose key in Ubuntu/Mint
#define COMPOSE KC_SCROLLLOCK

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  LAYOUT,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT( \
  F(0),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    	KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_ESC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    	KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    	KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    	KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  KC_LCTL, ADJUST,  KC_LGUI, KC_LALT, LOWER,   KC_ENT,  	KC_SPC,  RAISE,   KC_RALT, KC_APP,  COMPOSE, KC_RCTL \
),

[_LOWER] = LAYOUT( \
  KC_GRV, 	KC_EXLM, KC_EQUAL,  KC_SLSH, 	KC_ASTR, 	KC_PERC, 		KC_CIRC, 	   KC_AMPR, 	KC_ASTR,    	KC_LPRN, 	    KC_RPRN, 	  KC_ESC, \
  KC_TILD, 	KC_EXLM, KC_7,   	  KC_8, 		KC_9,  		KC_ASTR, 		KC_PLUS, 	   KC_ASTR, 	KC_LBRACKET, 	KC_RBRACKET, 	RALT(KC_S), KC_DEL, \
  KC_BSPC,  KC_AT,   KC_4,   	  KC_5,   	KC_6,   	KC_PERC,   	KC_MINUS,    KC_UNDS, 	KC_LPRN, 		  KC_RPRN, 		  KC_BSLASH, 	KC_APPLICATION, \
  KC_HASH, 	KC_DLR,  KC_1,   	  KC_2,   	KC_3,  		KC_ENT,  		KC_EQUAL,	   KC_SLSH,	  KC_LCBR, 		  KC_RCBR, 		  KC_PIPE, 	  KC_MPRV, \
  _______, 	KC_COMM, KC_0, 		  KC_DOT, 	_______, 	_______, 		_______, 	   _______, 	KC_MNXT, 		  KC_VOLD, 	    KC_VOLU, 	  KC_MPLY \
),

[_RAISE] = LAYOUT( \
  KC_F12,  KC_F1,         KC_F2,        KC_F3,        KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,   KC_F9,     KC_F10,  	KC_F11, \
  KC_GRV,  KC_MS_BTN1, 	  KC_MS_UP,   	KC_MS_BTN2, 	_______,    _______,  	_______,    KC_HOME,	  KC_END,  KC_PGDOWN, KC_PGUP, 	KC_DEL, \
  KC_DEL,  KC_MS_LEFT,    KC_MS_DOWN,		KC_MS_RIGHT,	_______,    _______,  	KC_INS,	    KC_LEFT, 	  KC_DOWN, KC_UP,     KC_RGHT, 	KC_APPLICATION, \
  _______, KC_MS_ACCEL0,  KC_MS_ACCEL1,	KC_MS_ACCEL2, _______,    _______,  	KC_MUTE,    KC_MPRV, 	  KC_VOLD, KC_VOLU,   KC_MNXT,	KC_MPLY, \
  _______, _______, 	    _______, 		  _______, 		  _______,    _______, 		_______,    _______, 	  BL_TOGG, BL_DEC,    BL_INC, 	KC_PSCREEN \
),

[_ADJUST] =  LAYOUT( \
  KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,      KC_F9,        KC_F10,  	            KC_F11, \
  _______,  RESET  , _______, _______, _______, _______, 	_______, KC_F2,   KC_F5,      LALT(KC_F4),  LCTL(LALT(KC_DEL)), 	KC_ESC, \
  KC_DEL,   _______, _______, _______, _______, _______, 	_______, KC_LEFT, KC_DOWN,    KC_UP,   	    KC_RGHT, 			        KC_APPLICATION, \
  _______,  _______, _______, BL_DEC,  BL_TOGG, BL_INC , 	_______, _______, _______,    _______, 	    _______, 			        _______, \
  LAYOUT,   _______, _______, _______, _______, _______, 	_______, _______, _______,    _______,  	  _______,  			      _______	\
)


};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

// grave escape (-> KC_GESC should do the same thing without custom code)
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
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

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
    case LAYOUT:
      if (record->event.pressed) {
        SEND_STRING("Lower:\n");
        SEND_STRING(",------------------------------------------------------------------------------------.\n");
        SEND_STRING("|   `  |   !  |   =  |   /  |   *  |   %  ||  ^   |   &  |   *  |   (  |   )  |  Esc |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|   ~  |   !  |   7  |   8  |   9  |   *  ||  +   |   *  |   [  |   ]  | GerS |  Del |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("| Bspc |   @  |   4  |   5  |   6  |   %  ||  -   |   _  |   (  |   )  |BckSlh|  App |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|   #  |   $  |   1  |   2  |   3  |Enter ||  =   |   /  |   {  |   }  |   |  | Prev |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|      |   ,  |   0  |   .  |      |      ||      |      | Next | Vol- | Vol+ | Play |\n");
        SEND_STRING("`------------------------------------------------------------------------------------'\n");
        SEND_STRING("Raise:\n");
        SEND_STRING(",------------------------------------------------------------------------------------.\n");
        SEND_STRING("|  F12 |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|   `  |RClick| MsUp |LClick|      |      ||      |      | Home |  End |PgDown| PgUp |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|  Del |MsLeft|MsDown|MsRigt|      |      ||Insert| Left | Down |  Up  | Right|  App |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|      |MsAcc0|MsAcc1|MsAcc2|      |      || Mute | Prev | Next | Vol- | Vol+ | Play |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|      |      |      |      |      |      ||      |      | BlTog|  Bl- |  Bl+ |PrScrn|\n");
        SEND_STRING("`------------------------------------------------------------------------------------'\n");
        SEND_STRING("Adjust:\n");
        SEND_STRING(",------------------------------------------------------------------------------------.\n");
        SEND_STRING("|  F12 |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|      | Reset|      |      |      |      ||      |  F2  |  F5  |Alt+F4| CADel|  Esc |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|  Del |      |      |      |      |      ||      | Left | Down |  Up  | Right|  App |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|      |      |      |  Bl- | BlTog|  Bl+ ||      |      |      |      |      |      |\n");
        SEND_STRING("|------+------+------+------+------+--------------+------+------+------+------+------|\n");
        SEND_STRING("|Layout|      |      |      |      |      ||      |      |      |      |      |      |\n");
        SEND_STRING("`------------------------------------------------------------------------------------'\n");
      }
      return false;
      break;
  }
  return true;
}
