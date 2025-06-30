#pragma once
#include <pico/stdlib.h>
#include <pico/rand.h>

#include "sprites.h"
#include "defs.h"
#include "framebuffer.h"

#define PIPE_COUNT DISPLAY_WIDTH / PIPE_SPACING + 2
#define PIPE_MIN_X -PIPE_WIDE_WIDTH // Minimum x-value of the pipe before it is despawned

extern int pipe_furthest_x;

struct pipe_t {
    int x_1024x;
    uint8_t height;
};

extern struct pipe_t pipes[PIPE_COUNT];

void pipe_initialise();
void pipe_tick(uint64_t engine_tick_count, bool player_is_dead, bool player_activated);

void _pipe_draw(struct pipe_t pipe);
struct pipe_t _pipe_generate();