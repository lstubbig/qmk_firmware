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
// #define LAYOUT_kc( \
//     A1, A2, A3, \
//     B1, B2, B3, \
//     C1, C2, C3  \
// ) \
//     LAYOUT_ortho_3x3( \
//         A1, A2, A3, \
//         B1, B2, B3, \
//         C1, C2, C3  \
//     )
#define LAYOUT(          \
      k00, k01, k02,     \
      k10, k11, k12         \
) {                      \
    { k00, k01, k02 }, \
    { k10, k11, k12 }, \
}