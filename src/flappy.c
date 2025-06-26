#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "display.h"
#include "framebuffer.h"
#include "sprites.h"

int main() {
    stdio_init_all();

    // I2C Initialisation. Using it at 1MHz for fun, it seems to handle it just fine up to 3MHz :)
    i2c_init(I2C_PORT, 1000 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Initialise the display, set it blank
    buffer_initialise();
    display_initialise();

    buffer_write_bitmap(birdFrames[0], (uint8_t)sizeof(birdFrames[0]) / sizeof(uint8_t), 0, 0, false);
    display_write(bufferPages);

    while (true) {
        tight_loop_contents();
    }
}