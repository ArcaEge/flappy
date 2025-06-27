/*
    Game engine logic
*/
#pragma once

#include <pico/stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "input_handler.h"
#include "display.h"
#include "framebuffer.h"

void game_engine_initialise();
void game_engine_start();

void _game_engine_tick();