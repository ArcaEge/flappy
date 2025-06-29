#include "game_engine.h"

/// @brief Incremented for each tick. Using uint64_t because hey, what if the player plays the game for two decades straight?
uint64_t engine_tick_count = 0;

/// @brief Initialise the game engine
void game_engine_initialise() {
    input_handler_initialise();
    pipe_initialise();
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
    engine_tick_count++;

    buffer_clear();

    // Handle inputs
    bool buttonPressed = input_handler_get_button_pressed();

    // Pipes
    pipe_tick(engine_tick_count, player_is_dead);

    // Player
    player_tick(buttonPressed, engine_tick_count);

    // Display
    display_write(bufferPages);
}