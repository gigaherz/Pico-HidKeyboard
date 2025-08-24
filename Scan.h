/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2025 David Quintana <gigaherz@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef enum KeyCode_t {
  KC_TAB = 0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQUALS, KC_BACKSPACE,
  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_KBRACE, KC_RBRACE, KC_BACKSLASH,
  KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_RETURN,
  KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_PERIOD, KC_SLASH, KC_UP_ARROW, KC_RIGHT_SHIFT,
  KC_FN, KC_CTRL, KC_BACK, KC_HOME, KC_SPACE, KEY_NC1, KEY_NC2, KEY_NC3, KEY_NC4, KC_RIGHT_ALT, KC_LEFT_ARROW, KC_DOWN_ARROW, KC_RIGHT_ARROW,
  KC___COUNT
} KeyCode;

// Called from main.cpp
void Scan__Init();
bool Scan__Tick();

// Called from Mapping.cpp
bool Scan__IsDown(KeyCode kc);
