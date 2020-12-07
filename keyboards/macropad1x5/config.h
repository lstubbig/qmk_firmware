/*
Copyright 2020 Leon Stubbig <leonstubbig@web.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0801
#define PRODUCT_ID      0x1133
#define DEVICE_VER      0x0100
#define MANUFACTURER    Leon Stubbig
#define PRODUCT         Macropad1x5
#define DESCRIPTION     1x5 Macropad with Rotary Encoder

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 5

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { B6, E6, D4, C6, D7} \
}

// encoder
#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }
#define ENCODER_RESOLUTION 4

// backlight
#define BACKLIGHT_PIN F7
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE