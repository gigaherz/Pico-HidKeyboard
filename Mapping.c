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
#include "Common.h"
#include "Pins.h"
#include "bsp/board_api.h"

#define CAT_NORMAL 0
#define CAT_CONSUMER 1
#define CAT_MODIFIER 2
typedef struct key_def_t
{
    int16_t cat : 3;
    int16_t key : 13;
#if SERIAL_DEBUG
    const char *debug_name;
#endif
} key_def;

#if SERIAL_DEBUG
#define N(k) {CAT_NORMAL, k, #k}
#define C(k) {CAT_CONSUMER, k, #k}
#define M(k) {CAT_MODIFIER, k, #k}
#define NOKEY {-1, -1, nullptr}
#define SPECIAL(name) {-1, -1, name}
#else
#define N(k) {CAT_NORMAL, k}
#define C(k) {CAT_CONSUMER, k}
#define M(k) {CAT_MODIFIER, k}
#define NOKEY {-1, -1}
#define SPECIAL(name) {-1, -1}
#endif

const key_def key_codes[MATRIX_SIZE] = {
    N(KEY_TAB), N(KEY_1), N(KEY_2), N(KEY_3), N(KEY_4), N(KEY_5), N(KEY_6), N(KEY_7), N(KEY_8), N(KEY_9), N(KEY_0), N(KEY_EQUAL), N(KEY_BACKSPACE),                                             //
    N(KEY_Q), N(KEY_W), N(KEY_E), N(KEY_R), N(KEY_T), N(KEY_Y), N(KEY_U), N(KEY_I), N(KEY_O), N(KEY_P), N(KEY_LEFT_BRACE), N(KEY_RIGHT_BRACE), N(KEY_BACKSLASH),                                //
    N(KEY_CAPS_LOCK), N(KEY_A), N(KEY_S), N(KEY_D), N(KEY_F), N(KEY_G), N(KEY_H), N(KEY_J), N(KEY_K), N(KEY_L), N(KEY_SEMICOLON), N(KEY_QUOTE), N(KEY_RETURN),                                  //
    M(MOD_LEFT_SHIFT), N(KEY_Z), N(KEY_X), N(KEY_C), N(KEY_V), N(KEY_B), N(KEY_N), N(KEY_M), N(KEY_COMMA), N(KEY_PERIOD), N(KEY_SLASH), N(KEY_UP_ARROW), M(MOD_RIGHT_SHIFT),                    //
    SPECIAL("KEY_FN"), M(MOD_LEFT_CTRL), N(KEY_ESC), N(KEY_LEFT_WINDOWS), N(KEY_SPACE), NOKEY, NOKEY, NOKEY, NOKEY, M(MOD_RIGHT_ALT), N(KEY_LEFT_ARROW), N(KEY_DOWN_ARROW), N(KEY_RIGHT_ARROW), //
};

const key_def key_codes_fn[MATRIX_SIZE] = {
    N(KEY_ESC), C(CONSUMER_BRIGHTNESS_DOWN), C(CONSUMER_BRIGHTNESS_UP), N(KEY_CUT), N(KEY_COPY), N(KEY_PASTE), C(MEDIA_PREV), C(MEDIA_PLAY_PAUSE), C(MEDIA_NEXT), C(CONSUMER_VOLUME_MUTE), C(CONSUMER_VOLUME_DOWN), C(CONSUMER_VOLUME_UP), NOKEY, //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
};

const key_def key_codes_fn_shift[MATRIX_SIZE] = {
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, N(KEY_FIND), NOKEY, //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
};

const uint8_t keys_error_report[6] = {1,1,1,1,1,1};
uint8_t keys_down[80];
int keys_down_c = 0;
bool keys_down_e = false;
bool changes = false;
uint8_t keys_modifier_bits;

const uint16_t consumer_error_report[1] = {0};
uint16_t consumer_down[6];
int consumer_down_c = 0;
bool consumer_down_e = false;
bool consumer_change = false;

void pressMod(int16_t key)
{
    keys_modifier_bits |= key;
    changes = true;
}
void releaseMod(int16_t key)
{
    keys_modifier_bits &= ~key;
    changes = true;
}

void pressKey(int16_t key)
{
    bool found = false;
    for(int i=0;i<keys_down_c;i++)
    {
        if (keys_down[i] == key)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        keys_down[keys_down_c++] = key;
        keys_down_e = keys_down_c > 6;
    }

    changes = true;
}
void releaseKey(int16_t key)
{
    int found = -1;
    for(int i=0;i<keys_down_c;i++)
    {
        if (keys_down[i] == key)
        {
            found = i;
            break;
        }
    }

    if (found >= 0)
    {
        keys_down_c--;
        if (found < keys_down_c)
            keys_down[found] = keys_down[keys_down_c];
        keys_down[keys_down_c] = 0;
        keys_down_e = keys_down_c > 6;
    }

    changes = true;
}

void pressCon(int16_t key)
{
    bool found = false;
    for(int i=0;i<consumer_down_c;i++)
    {
        if (consumer_down[i] == key)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        consumer_down[consumer_down_c++] = key;
        consumer_down_e = consumer_down_c > 1;
    }

    changes = true;
}
void releaseCon(int16_t key)
{
    int found = -1;
    for(int i=0;i<consumer_down_c;i++)
    {
        if (consumer_down[i] == key)
        {
            found = i;
            break;
        }
    }

    if (found >= 0)
    {
        consumer_down_c--;
        if (found < consumer_down_c)
            consumer_down[found] = consumer_down[consumer_down_c];
        consumer_down[consumer_down_c] = 0;
        consumer_down_e = consumer_down_c > 1;
    }

    changes = true;
}

void Mapping__Init()
{
    memset(keys_down,0,sizeof(keys_down));
    memset(consumer_down,0,sizeof(consumer_down));
}

bool Mapping__PendingChanges()
{
    bool b =  changes;
    changes = false;
    return b;
}

const uint8_t* Mapping__GetKeyboard()
{
    return keys_down_e ? keys_error_report : keys_down;
}

const uint16_t* Mapping__GetConsumer()
{
    return consumer_down_e ? consumer_error_report : consumer_down;
}

uint8_t Mapping__GetModifiers()
{
    return keys_modifier_bits;
}

void Mapping__KeyStateChange(KeyCode kc, bool state)
{
    key_def key = Scan__IsDown(KC_FN)
                      ? (Scan__IsDown(KC_CTRL) ? key_codes_fn_shift[kc] : key_codes_fn[kc])
                      : key_codes[kc];
    if (key.key >= 0)
    {
        switch (key.cat)
        {
        case CAT_NORMAL:
            if (state)
                pressKey(key.key);
            else
                releaseKey(key.key);
            break;
        case CAT_CONSUMER:
            if (state)
                pressCon(key.key);
            else
                releaseCon(key.key);
            break;
        case CAT_MODIFIER:
            if (state)
                pressMod(key.key);
            else
                releaseMod(key.key);
            break;
        }
    }
}
