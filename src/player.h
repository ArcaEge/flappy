#pragma once

#include <pico/stdlib.h>

#include "sprites.h"
#include "defs.h"
#include "framebuffer.h"
#include "game_engine.h"

#define PLAYER_HEIGHT ((uint8_t)sizeof(birdFrames[0]) / sizeof(uint8_t))
#define PLAYER_MIN_Y -((uint8_t)sizeof(birdFrames[0]) / 2)

extern const int player_x_1024x;
extern int player_y_1024x;

extern int player_velocity;

void player_tick(bool buttonPressed, uint64_t engine_tick_count);