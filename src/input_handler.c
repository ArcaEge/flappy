#include "input_handler.h"

volatile bool _input_handler_button_pressed = false;

void input_handler_initialise() {
    // Set the button GPIO as a pulled-down input
    gpio_init(INPUT_BUTTON_GPIO);
    gpio_set_dir(INPUT_BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(INPUT_BUTTON_GPIO);

    // Initialise the input interrupt
    // gpio_set_irq_enabled_with_callback is a thing, but I'm trying to remove abstractions where possible
    gpio_set_irq_enabled(INPUT_BUTTON_GPIO, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_callback(_input_handler_irq_callback);
    irq_set_enabled(IO_IRQ_BANK0, true);
}

/// @brief Get whether the button was pressed in the last tick cycle.
/// @return True if the button was pressed, false if not
bool input_handler_get_button_pressed() {
    if (_input_handler_button_pressed) {
        _input_handler_button_pressed = false;
        return true;
    }
    return false;
}

void _input_handler_irq_callback(uint gpio, uint32_t event_mask) {
    // No need to check gpio and event_mask as there's only 1 interrupt
    // This can somewhat act as a debouncer (albeit a pretty bad one) as the tick frequency isn't too high
    _input_handler_button_pressed = true;
}