#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0801
#define PRODUCT_ID      0x0801
#define DEVICE_VER      0x0620
#define MANUFACTURER    lstubbig
#define PRODUCT         macropad3x3
#define DESCRIPTION     3x3 macropad by Leon Stubbig

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { F7, F6, F4 }
#define MATRIX_COL_PINS { F4, F1, F0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
// #define BACKLIGHT_PIN B5
// #define BACKLIGHT_LEVELS 6

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#endif
