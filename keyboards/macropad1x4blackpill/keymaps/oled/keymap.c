/* Copyright 2020 Sergey Vlasov <sigprof@gmail.com>
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

enum tap_dances {
    TD_OLED,
};

enum oled_test_modes {
    // Modes between TEST_FIRST and TEST_LAST (inclusive) can be switched with a keypress.
    TEST_FIRST,
    TEST_LAYER = TEST_FIRST,
    TEST_LOGO,
    TEST_CHARACTERS,
    TEST_ALL_ON,
    TEST_FRAME,
    TEST_ALL_OFF,
    TEST_FILL_HORZ_0,
    TEST_FILL_HORZ_1,
    TEST_FILL_VERT_0,
    TEST_FILL_VERT_1,
    TEST_FILL_CHECKERBOARD_1,
    TEST_FILL_CHECKERBOARD_2,
    TEST_FILL_CHECKERBOARD_4,
    TEST_LAST = TEST_FILL_CHECKERBOARD_4,

    // Special modes which are not reachable normally.
    TEST_DRAW_ALWAYS_ON,
    TEST_DRAW_ALWAYS_OFF,
};

static enum oled_test_modes test_mode = TEST_FIRST;

static oled_rotation_t rotation = OLED_ROTATION_0;

static bool     scrolling;
static uint8_t  scrolling_speed;
static bool     need_update = true;
static bool     draw_always;
static bool     restart_test;

static void stop_scrolling(void) {
    if (scrolling) {
        oled_scroll_off();
        scrolling = false;
    }
}

static void dance_oled_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed) {
                // single hold - step through rotations
                switch (rotation) {
                    case OLED_ROTATION_0:
                        rotation = OLED_ROTATION_90;
                        break;
                    case OLED_ROTATION_90:
                        rotation = OLED_ROTATION_180;
                        break;
                    case OLED_ROTATION_180:
                        rotation = OLED_ROTATION_270;
                        break;
                    default:
                        rotation = OLED_ROTATION_0;
                        break;
                }
                stop_scrolling();
                oled_init(rotation);
            } else {
                // single tap - step through test modes
                if (test_mode < TEST_LAST) {
                    ++test_mode;
                } else {
                    test_mode = TEST_FIRST;
                }
                stop_scrolling();
                oled_clear();
            }
            restart_test = true;
            need_update  = true;
            break;

        case 2:
            if (state->pressed) {
                // tap + hold - change scrolling speed
                scrolling_speed = (scrolling_speed + 1) % 8;
                stop_scrolling();
                oled_scroll_set_speed(scrolling_speed);
                // Cannot reactivate scrolling here, because oled_scroll_off()
                // marks the whole display as dirty, and oled_scroll_left()
                // silently does nothing if either the display is dirty or
                // scrolling is already active.
            } else {
                // double tap - toggle scrolling
                if (!scrolling) {
                    scrolling = true;
                    oled_scroll_left();
                } else {
                    scrolling = false;
                    oled_scroll_off();
                }
            }
            need_update = true;
            break;

        case 3:
            if (state->pressed) {
                // double tap + hold - toggle `draw_always`
                draw_always = !draw_always;
                if (draw_always) {
                    test_mode = TEST_DRAW_ALWAYS_ON;
                } else {
                    test_mode = TEST_DRAW_ALWAYS_OFF;
                }
                stop_scrolling();
                oled_clear();
                restart_test = true;
                need_update  = true;
            } else {
                // triple tap - toggle update speed test
                // change to other layer?
            }
            break;
        case 4:
            if (!state->pressed) {
                // quadruple tap - step through brightness levels
                oled_set_brightness(oled_get_brightness() + 0x10);
            }
            break;
        default:
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {[TD_OLED] = ACTION_TAP_DANCE_FN(dance_oled_finished)};

enum layer_names {
    _Media,
    _Oled,
    _Backlight,
    _Blaaa
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_Media] =      LAYOUT_ortho_1x4(MO(_Oled), KC_VOLD,      KC_VOLU,  KC_MPLY),
    [_Oled] =       LAYOUT_ortho_1x4(_______,   TD(TD_OLED),  KC_A,     RESET),
    [_Backlight] =  LAYOUT_ortho_1x4(_______,   BL_DEC,       BL_INC,   BL_BRTG)
};

// `bool oled_is_dirty(void)` does not exist at the moment
extern OLED_BLOCK_TYPE oled_dirty;

static inline uint8_t pixel_width(void) {
    if (!(rotation & OLED_ROTATION_90)) {
        return OLED_DISPLAY_WIDTH;
    }
    return OLED_DISPLAY_HEIGHT;
}

static inline uint8_t pixel_height(void) {
    if (!(rotation & OLED_ROTATION_90)) {
        return OLED_DISPLAY_HEIGHT;
    }
    return OLED_DISPLAY_WIDTH;
}

// Draw the QMK logo at the top left corner, clipping if it does not fit.
static void test_logo(void) {
    uint8_t lines = oled_max_lines();
    if (lines > 3) {
        lines = 3;
    }
    uint8_t chars = oled_max_chars();
    if (chars > 21) {
        chars = 21;
    }
    for (uint8_t row = 0; row < lines; ++row) {
        oled_set_cursor(0, row);
        for (uint8_t col = 0; col < chars; ++col) {
            oled_write_char(0x80 + 0x20 * row + col, false);
        }
    }
}

static const PROGMEM char fill_ff[OLED_MATRIX_SIZE] = {[0 ... OLED_MATRIX_SIZE - 1] = 0xff};

// Fill the whole screen with a pattern made from two bytes alternating after the specified number of repeats.
static void test_fill(uint8_t byte0, uint8_t byte1, uint8_t repeats) {
    uint8_t  width = pixel_width();
    uint8_t  lines = oled_max_lines();
    uint16_t index = 0;
    for (uint8_t row = 0; row < lines; ++row) {
        for (uint8_t col = 0; col < width; ++col) {
            uint8_t byte = ((col / repeats) % 2) ? byte1 : byte0;
            oled_write_raw_byte(byte, index++);
        }
    }
}

// Draw a frame at the edges of the OLED screen.
static void test_frame(void) {
    uint8_t width  = pixel_width();
    uint8_t height = pixel_height();
    for (uint8_t x = 0; x < width; ++x) {
        oled_write_pixel(x, 0, true);
        oled_write_pixel(x, height - 1, true);
    }
    for (uint8_t y = 1; y < height - 1; ++y) {
        oled_write_pixel(0, y, true);
        oled_write_pixel(width - 1, y, true);
    }
}

// Use all 94 visible ASCII characters for testing.
#define TEST_CHAR_COUNT ('~' - '!' + 1)

static char get_test_char(uint8_t char_index) { return char_index + '!'; }

// Fill the whole screen with distinct characters (if the display is large enough to show more than 94 characters
// at once, the sequence is repeated the second time with inverted characters).
__attribute__((unused)) static void test_characters(void) {
    uint8_t cols       = oled_max_chars();
    uint8_t rows       = oled_max_lines();
    bool    invert     = false;
    uint8_t char_index = 0;
    for (uint8_t row = 0; row < rows; ++row) {
        for (uint8_t col = 0; col < cols; ++col) {
            oled_write_char(get_test_char(char_index), invert);
            if (++char_index >= TEST_CHAR_COUNT) {
                char_index = 0;
                invert     = !invert;
            }
        }
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_scroll_set_area(0, 3);
    // oled_scroll_set_speed(scrolling_speed);
    oled_scroll_set_speed(0);
    return rotation;
}

void oled_task_user(void) {
    switch (test_mode) {
        case TEST_LAYER:
            test_logo();
            oled_write_P(PSTR("      Layer: "), false);
            //switch (get_highest_layer(layer_state)) {
            switch (get_highest_layer(layer_state)) {
                case _Oled:
                    oled_write_P(PSTR("Oled\n"), false);
                    break;
                case _Media:
                    oled_write_P(PSTR("Media\n"), false);
                    break;
                default:
                    // Or use the write_ln shortcut over adding '\n' to the end of your string
                    oled_write_ln_P(PSTR("Hello there."), false);
            }
            break;
        case TEST_LOGO:
            test_logo();
            break;
        case TEST_CHARACTERS:
            test_characters();
            break;
        case TEST_ALL_ON:
            oled_write_raw_P(fill_ff, sizeof(fill_ff));
            break;
        case TEST_FRAME:
            test_frame();
            break;
        case TEST_ALL_OFF:
            // oled_clear(); // only clears top left
            test_fill(0x00, 0x00, 1);
            break;
        case TEST_FILL_HORZ_0:
            test_fill(0x55, 0x55, 1);
            break;
        case TEST_FILL_HORZ_1:
            test_fill(0xaa, 0xaa, 1);
            break;
        case TEST_FILL_VERT_0:
            test_fill(0xff, 0x00, 1);
            break;
        case TEST_FILL_VERT_1:
            test_fill(0x00, 0xff, 1);
            break;
        case TEST_FILL_CHECKERBOARD_1:
            test_fill(0x55, 0xaa, 1);
            break;
        case TEST_FILL_CHECKERBOARD_2:
            test_fill(0x33, 0xcc, 2);
            break;
        case TEST_FILL_CHECKERBOARD_4:
            test_fill(0x0f, 0xf0, 4);
            break;
        case TEST_DRAW_ALWAYS_ON:
            oled_write_P(PSTR("Draw Always"), false);
            break;
        case TEST_DRAW_ALWAYS_OFF:
            oled_write_P(PSTR("Draw Once"), false);
            break;
    }
}

// void oled_task_user(void) {
//     test_logo();

//     // Host Keyboard Layer Status
//     // oled_set_cursor(0, 3);
//     oled_write_P(PSTR("      Layer: "), false);
//     switch (get_highest_layer(layer_state)) {
//         case _Oled:
//             oled_write_P(PSTR("OLED\n"), false);
//             break;
//         case _Media:
//             oled_write_P(PSTR("Media\n"), false);
//             break;
//         default:
//             // Or use the write_ln shortcut over adding '\n' to the end of your string
//             oled_write_ln_P(PSTR("Hello there."), false);
//     }
// }
