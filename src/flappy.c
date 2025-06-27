#include <pico/stdlib.h>
#include <stdio.h>

#include "display.h"
#include "framebuffer.h"
#include "game_engine.h"

int main() {
    stdio_init_all();

    // Initialise everything
    buffer_initialise();
    display_initialise();
    display_write(bufferPages);
    game_engine_initialise();

    // Start the game engine main loop
    game_engine_start();
}