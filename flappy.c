#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "defs.h"
#include "display.h"


int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    display_initialise();

    while (true) {
        set_display_state(true);
        sleep_ms(1000);
        set_display_state(false);
        sleep_ms(1000);
    }
}
