#include "Common.hpp"
#include "Pins.hpp"

typedef struct key_def_t
{
    int16_t cat : 3;
    int16_t key : 13;
#if SERIAL_DEBUG
    const char *debug_name;
#endif
} key_def;

#if SERIAL_DEBUG
#define N(k) {0, k, #k}
#define C(k) {1, k, #k}
#define NOKEY {-1, -1, nullptr}
#define SPECIAL(name) {-1, -1, name}
#else
#define N(k) {0, k}
#define C(k) {1, k}
#define NOKEY {-1, -1}
#define SPECIAL(name) {-1, -1}
#endif

const key_def key_codes[] = {
    N(KEY_TAB), N(KEY_1), N(KEY_2), N(KEY_3), N(KEY_4), N(KEY_5), N(KEY_6), N(KEY_7), N(KEY_8), N(KEY_9), N(KEY_0), N(KEY_EQUAL), N(KEY_BACKSPACE),                                             //
    N(KEY_Q), N(KEY_W), N(KEY_E), N(KEY_R), N(KEY_T), N(KEY_Y), N(KEY_U), N(KEY_I), N(KEY_O), N(KEY_P), N(KEY_LEFT_BRACE), N(KEY_RIGHT_BRACE), N(KEY_BACKSLASH),                                //
    N(KEY_CAPS_LOCK), N(KEY_A), N(KEY_S), N(KEY_D), N(KEY_F), N(KEY_G), N(KEY_H), N(KEY_J), N(KEY_K), N(KEY_L), N(KEY_SEMICOLON), N(KEY_QUOTE), N(KEY_RETURN),                                  //
    N(KEY_LEFT_SHIFT), N(KEY_Z), N(KEY_X), N(KEY_C), N(KEY_V), N(KEY_B), N(KEY_N), N(KEY_M), N(KEY_COMMA), N(KEY_PERIOD), N(KEY_SLASH), N(KEY_UP_ARROW), N(KEY_RIGHT_SHIFT),                    //
    SPECIAL("KEY_FN"), N(KEY_LEFT_CTRL), N(KEY_ESC), N(KEY_LEFT_WINDOWS), N(KEY_SPACE), NOKEY, NOKEY, NOKEY, NOKEY, N(KEY_RIGHT_ALT), N(KEY_LEFT_ARROW), N(KEY_DOWN_ARROW), N(KEY_RIGHT_ARROW), //
};
const int key_codes_count = countof(key_codes);
#if key_codes_count != MATRIX_SIZE
#error matrix mismatch
#endif

const key_def key_codes_fn[] = {
    N(KEY_ESC), C(CONSUMER_BRIGHTNESS_DOWN), C(CONSUMER_BRIGHTNESS_UP), N(KEY_CUT), N(KEY_COPY), N(KEY_PASTE), C(MEDIA_PREV), C(MEDIA_PLAY_PAUSE), C(MEDIA_NEXT), N(KEY_VOLUME_MUTE), N(KEY_VOLUME_DOWN), N(KEY_VOLUME_UP), NOKEY, //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,                                                                                                                                     //
};
const int key_codes_fn_count = countof(key_codes_fn);
#if key_codes_fn_count != MATRIX_SIZE
#error matrix mismatch
#endif

const key_def key_codes_fn_shift[] = {
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, N(KEY_FIND), NOKEY, //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
    NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,       //
};
const int key_codes_fn_shift_count = countof(key_codes_fn_shift);
#if key_codes_fn_shift != MATRIX_SIZE
#error matrix mismatch
#endif

const uint8_t keys_error_report[6] = {1,1,1,1,1,1};
uint8_t keys_down[KEY__COUNT];
int keys_down_c = 0;
int keys_down_c0 = 0;
bool keys_down_e = false;
bool keys_down_e0 = false;
bool keys_change = false;

const uint16_t consumer_error_report[1] = {0};
uint16_t consumer_down[CONSUMER__COUNT];
int consumer_down_c = 0;
int consumer_down_c0 = 0;
bool consumer_down_e = false;
bool consumer_down_e0 = false;
bool consumer_change = false;

void press(HID_Keys key)
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
        keys_down_e = keys_down_c >= 6;
    }

    keys_change |= keys_down_c0 != keys_down_c || keys_down_e0 != keys_down_e;

    keys_down_c0 = keys_down_c;
    keys_down_e0 = keys_down_e;
}
void release(HID_Keys key)
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

    if (!found)
    {
        keys_down_c--;
        if (found < keys_down_c)
            keys_down[found] = keys_down[keys_down_c];
        keys_down[keys_down_c] = 0;
        keys_down_e = keys_down_c >= 6;
    }

    keys_change |= keys_down_c0 != keys_down_c || keys_down_e0 != keys_down_e;

    keys_down_c0 = keys_down_c;
    keys_down_e0 = keys_down_e;
}

void press(HID_Consumer key)
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
        consumer_down_e = consumer_down_c >= 6;
    }

    consumer_change |= consumer_down_c0 != consumer_down_c || consumer_down_e0 != consumer_down_e;

    consumer_down_c0 = consumer_down_c;
    consumer_down_e0 = consumer_down_e;
}
void release(HID_Consumer key)
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

    if (!found)
    {
        consumer_down_c--;
        if (found < consumer_down_c)
            consumer_down[found] = consumer_down[consumer_down_c];
        consumer_down[keys_down_c] = 0;
        consumer_down_e = consumer_down_c >= 6;
    }

    consumer_change |= consumer_down_c0 != consumer_down_c || consumer_down_e0 != consumer_down_e;

    consumer_down_c0 = consumer_down_c;
    consumer_down_e0 = consumer_down_e;
}

bool Mapping::KeyboardChanged()
{
    return keys_change;
}
bool Mapping::ConsumerChanged()
{
    return consumer_change;
}
const uint8_t* Mapping::GetKeyboard()
{
    return keys_down_e ? keys_error_report : keys_down;
}

const uint16_t* Mapping::GetConsumer()
{
    return consumer_down_e ? consumer_error_report : consumer_down;
}

void Mapping::KeyStateChange(KeyCode kc, bool state)
{
    key_def key = Scan::IsDown(KC_FN)
                      ? (Scan::IsDown(KC_CTRL) ? key_codes_fn_shift[kc] : key_codes_fn[kc])
                      : key_codes[kc];
    if (key.key >= 0)
    {
        switch (key.cat)
        {
        case 0:
            if (state)
                press((HID_Keys)key.key);
            else
                release((HID_Keys)key.key);
            break;
        case 1:
            if (state)
                press((HID_Consumer)key.key);
            else
                release((HID_Consumer)key.key);
            break;
        }
    }
}
