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
    [_Base] = LAYOUT(
        KC_7,               KC_8,           KC_9,
        LT(_Media, KC_4),   KC_5,           KC_6,
        LT(_Nav, KC_1),     LT(_Fn, KC_2),  LT(_Mouse, KC_3)
    ),
    [_Fn] = LAYOUT(
        QMKBEST,    QMKURL,     HALLO,
        KC_0,       KC_0,       KC_0,
        KC_0,       _______,    KC_0
    ),
    [_Nav] = LAYOUT(
        KC_HOME,    KC_UP,      KC_END,
        KC_LEFT,    KC_DOWN,    KC_RIGHT,
        LCTL(LALT(KC_V)),    KC_ENTER,   _______
    ),
    [_Nav2] = LAYOUT(
        LALT(KC_TAB),   _______,    _______,
        _______,        _______,    _______,
        _______,        _______,    _______
    ),
    [_Mouse] = LAYOUT(
        KC_MS_BTN1,    KC_MS_UP,      KC_MS_BTN2,
        KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_RIGHT,
        KC_ENTER,      KC_MS_BTN3,    _______
    ),
    [_Media] = LAYOUT(
        KC_MUTE,    KC_AUDIO_VOL_DOWN,      KC_AUDIO_VOL_UP,
        KC_S,       KC_MEDIA_PREV_TRACK,    KC_MEDIA_NEXT_TRACK,
        KC_F,       LT(_Nav2, KC_SPACE),    LT(_Nav, KC_MEDIA_PLAY_PAUSE)
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