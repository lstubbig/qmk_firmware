/* Copyright 2020 Leon Stubbig
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _Media,
    _Base,
    _Fn,
    _Nav,
    _Nav2,
    _Mouse
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    HALLO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_Base] = LAYOUT_ENCODER(
        KC_7,               KC_8,           KC_9,
        LT(_Media, KC_4),   KC_5,           KC_6,
        LT(_Nav, KC_1),     LT(_Fn, KC_2),  LT(_Mouse, KC_3),
        KC_MUTE
    ),
    [_Fn] = LAYOUT_ENCODER(
        QMKBEST,    QMKURL,     HALLO,
        KC_0,       KC_0,       KC_0,
        KC_0,       _______,    KC_0,
        _______
    ),
    [_Nav] = LAYOUT_ENCODER(
        KC_HOME,            KC_UP,      KC_END,
        KC_LEFT,            KC_DOWN,    KC_RIGHT,
        LCTL(LALT(KC_V)),   KC_ENTER,   _______,
        _______
    ),
    [_Nav2] = LAYOUT_ENCODER(
        LALT(KC_TAB),   _______,    _______,
        _______,        _______,    _______,
        _______,        _______,    _______,
        _______
    ),
    [_Mouse] = LAYOUT_ENCODER(
        KC_MS_BTN1,    KC_MS_UP,      KC_MS_BTN2,
        KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_RIGHT,
        KC_ENTER,      KC_MS_BTN3,    _______,
        _______
    ),
    [_Media] = LAYOUT_ENCODER(
        KC_MUTE,    KC_AUDIO_VOL_DOWN,      KC_AUDIO_VOL_UP,
        KC_S,       KC_MEDIA_PREV_TRACK,    KC_MEDIA_NEXT_TRACK,
        KC_F,       LT(_Nav2, KC_SPACE),    LT(_Nav, KC_MEDIA_PLAY_PAUSE),
        _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
        case HALLO:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("Hello there.");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
};

// encoder functions
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_UP);
        } else {
            tap_code(KC_AUDIO_VOL_DOWN);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}

// oled display functions
// #ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

void oled_task_user(void) {
    // oled_clear();
    // oled_render();

    // big logo
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);

    // Host Keyboard Layer Status
    // oled_set_cursor(0, 3);
    oled_write_P(PSTR("      Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _Base:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _Fn:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _Media:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case _Nav:
            // oled_set_cursor(14, 3);
            oled_write_P(PSTR("Nav\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Hello there."), false);
    }

    // // Host Keyboard LED Status
    // led_t led_state = host_keyboard_led_state();
    // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

}
// #endiff