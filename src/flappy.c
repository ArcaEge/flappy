#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "display.h"
#include "framebuffer.h"

int main() {
    stdio_init_all();

    // I2C Initialisation. Using it at 1MHz for fun, it seems to handle it just fine up to 3MHz :)
    i2c_init(I2C_PORT, 1000 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    buffer_initialise();
    display_initialise();

    // Switch on pixel (0, 0)
    buffer_set_pixel_state(0, 0, 0);

    display_write(bufferPages);

    while (true) {
        tight_loop_contents();
    }
}
