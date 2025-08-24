#pragma once
#include <stdint.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

typedef enum KeyCode_t : uint8_t {
  KC_TAB = 0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQUALS, KC_BACKSPACE,
  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_KBRACE, KC_RBRACE, KC_BACKSLASH,
  KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_RETURN,
  KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_PERIOD, KC_SLASH, KC_UP_ARROW, KC_RIGHT_SHIFT,
  KC_FN, KC_CTRL, KC_BACK, KC_HOME, KC_SPACE, KEY_NC1, KEY_NC2, KEY_NC3, KEY_NC4, KC_RIGHT_ALT, KC_LEFT_ARROW, KC_DOWN_ARROW, KC_RIGHT_ARROW,
  KC___COUNT
} KeyCode;

class Scan {
public:
    // Called from main.cpp
    static void Start();
    static void Stop();
    static void Tick();

    // Called from Mapping.cpp
    static bool IsDown(KeyCode kc);
};
