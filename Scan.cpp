#include "Common.hpp"
#include "Pins.hpp"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"
#include "bsp/board_api.h"

const int DEBOUNCE_TIME = 5;

typedef struct key_state_t
{
    uint8_t state : 1;
    uint8_t count : 7;
} key_state;

key_state last_state[MATRIX_SIZE];

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

//static bool timer_callback(__unused repeating_timer_t *rt);

//repeating_timer_t timer;

bool Scan::IsDown(KeyCode kc)
{
    if (kc >= 0 && kc <= MATRIX_SIZE)
        return last_state[kc].state;
    return false;
}

void Scan::Start()
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
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        last_state[i] = {0, 0};
    }

    // negative timeout means exact delay (rather than delay between callbacks)
    //add_repeating_timer_us(-1000, timer_callback, NULL, &timer);
}
void Scan::Stop()
{
  //cancel_repeating_timer(&timer);
}

//static bool timer_callback(__unused repeating_timer_t *rt)
void Scan::Tick()
{
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
                    old_state = {state, 0};
                    Mapping::KeyStateChange((KeyCode)kc, state);
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
    //return true;
}
