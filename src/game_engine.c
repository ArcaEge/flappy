#include "game_engine.h"

#include "sprites.h"

/// @brief Initialise the game engine
void game_engine_initialise() {
    input_handler_initialise();

    uint ret = buffer_write_bitmap(birdFrames[0], (uint8_t)sizeof(birdFrames[0]) / sizeof(uint8_t), 0, 0, false);
    printf("%d\n", ret);
    display_write(bufferPages);
    ret = buffer_write_bitmap(birdFrames[0], (uint8_t)sizeof(birdFrames[0]) / sizeof(uint8_t), 0, 0, true);
    printf("%d\n", ret);
    display_write(bufferPages);
    ret = buffer_write_bitmap(birdFrames[0], (uint8_t)sizeof(birdFrames[0]) / sizeof(uint8_t), 7, 0, false);
    printf("%d\n", ret);
    display_write(bufferPages);
}

/// @brief Starts the main loop of the game engine
void game_engine_start() {
    while (true) {
        _game_engine_tick();
        sleep_ms(GAME_ENGINE_TICK_PERIOD);
    }
}

/// @brief A single tick of the engine
void _game_engine_tick() {
    // Handle inputs
    bool buttonPressed = input_handler_get_button_pressed();

    // Movement and physics

    // Display
}