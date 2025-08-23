#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

bool timer_callback(__unused repeating_timer_t *rt);

repeating_timer_t timer;

int main()
{    
    // negative timeout means exact delay (rather than delay between callbacks)
    if (!add_repeating_timer_us(-1000, timer_callback, NULL, &timer)) {
        printf("Failed to add timer\n");
        return 1;
    }

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}


bool timer_callback(__unused repeating_timer_t *rt) {
    // Put your timeout handler code in here
    return 0;
}
