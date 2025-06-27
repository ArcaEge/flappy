/*
    Input handling using interrupts
*/
#pragma once

#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/irq.h>

#include "defs.h"

void input_handler_initialise();
bool input_handler_get_button_pressed();

void _input_handler_irq_callback(uint gpio, uint32_t event_mask);