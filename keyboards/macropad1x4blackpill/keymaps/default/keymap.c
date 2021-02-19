#include QMK_KEYBOARD_H

// macros
enum custom_keycodes {
    TROLL = SAFE_RANGE,
    QMKURL,
    MY_OTHER_MACRO,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x4(RESET, KC_VOLD, KC_VOLU, TROLL )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case TROLL:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("trollolol");
        } else {
        }
        break;
    }
    return true;
};
