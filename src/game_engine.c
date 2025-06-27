#include "game_engine.h"

/// @brief Initialise the game engine
void game_engine_initialise() {
    input_handler_initialise();
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
    bool buttonState = input_handler_get_button_pressed();
    if (buttonState) printf("WOOHOO BUTTON PRESSED LET'S GO!!!\n");

    // Movement and physics

    // Display
}