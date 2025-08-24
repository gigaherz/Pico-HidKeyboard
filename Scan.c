#include "Common.h"
#include "Pins.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"
#include "bsp/board_api.h"

const int cols[COLS] = {
  RIBBON_17, RIBBON_8, RIBBON_6, RIBBON_15, RIBBON_12, RIBBON_11, RIBBON_9, RIBBON_7, RIBBON_5, RIBBON_4, RIBBON_3, RIBBON_2, RIBBON_1
};

const int rows[ROWS] = {
  RIBBON_10, RIBBON_13, RIBBON_14, RIBBON_16, RIBBON_18
};

const int DEBOUNCE_TIME = 5;

typedef struct key_state_t
{
    uint8_t state : 1;
    uint8_t count : 7;
} key_state;

static key_state last_state[MATRIX_SIZE];

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3

static inline void pinMode(int pin, int mode)
{
    gpio_init(pin);
    switch (mode)
    {
    case OUTPUT:
        gpio_set_dir(pin, GPIO_OUT);
        break;
    case INPUT:
        gpio_set_dir(pin, GPIO_IN);
        break;
    case INPUT_PULLUP:
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_up(pin);
        break;
    case INPUT_PULLDOWN:
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_down(pin);
        break;
    }
}

static inline void digitalWrite(int pin, bool value)
{
    if (value)
        gpio_set_mask(1 << pin);
    else
        gpio_clr_mask(1 << pin);
}

static inline bool digitalRead(int pin)
{
    return gpio_get(pin);
}

bool Scan__IsDown(KeyCode kc)
{
    if (kc >= 0 && kc <= MATRIX_SIZE)
        return last_state[kc].state;
    return false;
}

void Scan__Init()
{
    for (int i = 0; i < COLS; i++)
    {
        int pin = cols[i];
        pinMode(pin, INPUT_PULLUP);
    }
    for (int i = 0; i < ROWS; i++)
    {
        int pin = rows[i];
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 1);
    }
    memset(last_state, 0, sizeof(last_state));
}

bool Scan__Tick()
{
    bool activity = false;
    for (int i = 0; i < ROWS; i++)
    {
        int pin_r = rows[i];
        digitalWrite(pin_r, 0);
        for (int j = 0; j < COLS; j++)
        {
            int pin_c = cols[j];
            uint8_t state = !digitalRead(pin_c);
            int kc = i * COLS + j;
            if (kc < 0 || kc >= MATRIX_SIZE)
            {
                continue;
            }
            key_state old_state = last_state[kc];
            if (state != old_state.state)
            {
                old_state.count++;
                if (old_state.count >= DEBOUNCE_TIME)
                {
                    old_state.state = state;
                    old_state.count = 0;
                    Mapping__KeyStateChange((KeyCode)kc, state);
                    activity = true;
                }
            }
            else
            {
                old_state.count = 0;
            }
            last_state[kc] = old_state;
        }
        digitalWrite(pin_r, 1);
    }
    return activity;
}
