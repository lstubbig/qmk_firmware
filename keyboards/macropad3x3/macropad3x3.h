#pragma once

#include "quantum.h"

#define LAYOUT_ortho_3x3( \
    A1, A2, A3, \
    B1, B2, B3, \
    C1, C2, C3  \
) { \
    { A1, A2, A3 }, \
    { B1, B2, B3 }, \
    { C1, C2, C3 }  \
}

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
    A1, A2, A3, \
    B1, B2, B3, \
    C1, C2, C3  \
) \
    LAYOUT_ortho_3x3( \
        KC_##A1, KC_##A2, KC_##A3, \
        KC_##B1, KC_##B2, KC_##B3, \
        KC_##C1, KC_##C2, KC_##C3  \
    )
