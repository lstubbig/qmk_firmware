/* Copyright 2021 Leon Stubbig
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
    _Nav,
    _FN,
    _FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_Media] = LAYOUT(
        KC_MUTE,    KC_AUDIO_VOL_DOWN,      KC_AUDIO_VOL_UP,
        KC_S,       KC_MEDIA_PREV_TRACK,    KC_MEDIA_NEXT_TRACK,
        KC_F,       KC_SPACE,               LT(_Nav, KC_MEDIA_PLAY_PAUSE)
    ),
    [_Nav] = LAYOUT(
        KC_HOME,            KC_UP,      KC_END,
        KC_LEFT,            KC_DOWN,    KC_RIGHT,
        LCTL(LALT(KC_V)),   KC_ENTER,   _______
    ),
    [_FN] = LAYOUT(
        _______,    _______,    _______,
        _______,    _______,    _______,
        _______,    _______,    _______
    ),
    [_FN2] = LAYOUT(
        _______,    _______,    _______,
        _______,    _______,    _______,
        _______,    _______,    _______
    )
};