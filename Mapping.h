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
#include <stdint.h>
#include "tusb.h"

enum HID_Keys_t {
    // Numbers
    KEY_1 = HID_KEY_1,
    KEY_2 = HID_KEY_2,
    KEY_3 = HID_KEY_3,
    KEY_4 = HID_KEY_4,
    KEY_5 = HID_KEY_5,
    KEY_6 = HID_KEY_6,
    KEY_7 = HID_KEY_7,
    KEY_8 = HID_KEY_8,
    KEY_9 = HID_KEY_9,
    KEY_0 = HID_KEY_0,

    // Letters
    KEY_Q = HID_KEY_Q,
    KEY_W = HID_KEY_W,
    KEY_E = HID_KEY_E,
    KEY_R = HID_KEY_R,
    KEY_T = HID_KEY_T,
    KEY_Y = HID_KEY_Y,
    KEY_U = HID_KEY_U,
    KEY_I = HID_KEY_I,
    KEY_O = HID_KEY_O,
    KEY_P = HID_KEY_P,
    KEY_A = HID_KEY_A,
    KEY_S = HID_KEY_S,
    KEY_D = HID_KEY_D,
    KEY_F = HID_KEY_F,
    KEY_G = HID_KEY_G,
    KEY_H = HID_KEY_H,
    KEY_J = HID_KEY_J,
    KEY_K = HID_KEY_K,
    KEY_L = HID_KEY_L,
    KEY_Z = HID_KEY_Z,
    KEY_X = HID_KEY_X,
    KEY_C = HID_KEY_C,
    KEY_V = HID_KEY_V,
    KEY_B = HID_KEY_B,
    KEY_N = HID_KEY_N,
    KEY_M = HID_KEY_M,

    // Symbols
    KEY_SPACE = HID_KEY_SPACE, 
    KEY_TAB = HID_KEY_TAB,
    KEY_EQUAL = HID_KEY_EQUAL,
    KEY_LEFT_BRACE = HID_KEY_BRACKET_LEFT,
    KEY_RIGHT_BRACE = HID_KEY_BRACKET_RIGHT,
    KEY_BACKSLASH = HID_KEY_BACKSLASH,
    KEY_CAPS_LOCK = HID_KEY_CAPS_LOCK,
    KEY_SEMICOLON = HID_KEY_SEMICOLON,
    KEY_QUOTE = HID_KEY_APOSTROPHE,
    KEY_COMMA = HID_KEY_COMMA,
    KEY_PERIOD = HID_KEY_PERIOD,
    KEY_SLASH = HID_KEY_SLASH,

    // Control
    KEY_RETURN = HID_KEY_RETURN,
    KEY_BACKSPACE = HID_KEY_BACKSPACE,
    KEY_ESC = HID_KEY_ESCAPE,
    KEY_LEFT_WINDOWS = HID_KEY_GUI_LEFT,
    KEY_RIGHT_WINDOWS = HID_KEY_GUI_RIGHT,
    KEY_MENU = HID_KEY_MENU,

    // Arrows
    KEY_UP_ARROW = HID_KEY_ARROW_UP,
    KEY_LEFT_ARROW = HID_KEY_ARROW_LEFT,
    KEY_DOWN_ARROW = HID_KEY_ARROW_DOWN,
    KEY_RIGHT_ARROW = HID_KEY_ARROW_RIGHT,

    // Media
    KEY_CUT = HID_KEY_CUT,
    KEY_COPY = HID_KEY_COPY,
    KEY_PASTE = HID_KEY_PASTE,
    KEY_FIND = HID_KEY_FIND,
};

enum HID_Modifiers_t {
    // Modifiers
    MOD_LEFT_SHIFT = KEYBOARD_MODIFIER_LEFTSHIFT,
    MOD_RIGHT_SHIFT = KEYBOARD_MODIFIER_RIGHTSHIFT,
    MOD_LEFT_CTRL = KEYBOARD_MODIFIER_LEFTCTRL,
    MOD_RIGHT_ALT = KEYBOARD_MODIFIER_RIGHTALT,
 };

enum HID_Consumer_t {
    CONSUMER_BRIGHTNESS_DOWN = HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT,
    CONSUMER_BRIGHTNESS_UP = HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT,
    MEDIA_PREV = HID_USAGE_CONSUMER_SCAN_PREVIOUS,
    MEDIA_PLAY_PAUSE = HID_USAGE_CONSUMER_PLAY_PAUSE,
    MEDIA_NEXT = HID_USAGE_CONSUMER_SCAN_NEXT,
    
    CONSUMER_VOLUME_MUTE = HID_USAGE_CONSUMER_MUTE,
    CONSUMER_VOLUME_DOWN = HID_USAGE_CONSUMER_VOLUME_DECREMENT,
    CONSUMER_VOLUME_UP = HID_USAGE_CONSUMER_VOLUME_INCREMENT
};

// Called by Scan.cpp
void Mapping__KeyStateChange(KeyCode kc, bool state);

// Called by main.cpp
void Mapping__Init();
bool Mapping__PendingChanges();
const uint8_t* Mapping__GetKeyboard();
const uint16_t* Mapping__GetConsumer();
uint8_t Mapping__GetModifiers();
