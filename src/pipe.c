#include "pipe.h"

int pipe_furthest_x = DISPLAY_WIDTH * 1024;
struct pipe_t pipes[PIPE_COUNT];

void pipe_initialise() {
    for (uint i = 0; i < PIPE_COUNT; i++) {
        pipes[i] = _pipe_generate();
    }
}

void pipe_tick(uint64_t engine_tick_count, bool player_is_dead, bool player_activated) {
    for (uint pipeNo = 0; pipeNo < PIPE_COUNT; pipeNo++) {
        if (!player_is_dead && player_activated) {
            pipes[pipeNo].x_1024x -= PIPE_SPEED;

            // Generate a new pipe if the pipe is off to the left side of the screen
            if (pipes[pipeNo].x_1024x / 1024 < PIPE_MIN_X)
                pipes[pipeNo] = _pipe_generate();
        }

        _pipe_draw(pipes[pipeNo]);
    }

    if (!player_is_dead && player_activated) {
        pipe_furthest_x -= PIPE_SPEED;
    }
}

/// @brief Draws a pair of pipes onto the framebuffer
/// @param pipe Pipe struct to draw
void _pipe_draw(struct pipe_t pipe) {
    int pipe_x = pipe.x_1024x / 1024;

    // Top pipe
    buffer_draw_rectangle(pipe_x + ((PIPE_WIDE_WIDTH - PIPE_NARROW_WIDTH) / 2), 0,
                          pipe_x + ((PIPE_WIDE_WIDTH - PIPE_NARROW_WIDTH) / 2) + PIPE_NARROW_WIDTH, PIPE_NARROW_MIN_HEIGHT + pipe.height);
    buffer_draw_rectangle(pipe_x, pipe.height + PIPE_OFFSET - PIPE_WIDE_HEIGHT,
                          pipe_x + PIPE_WIDE_WIDTH, pipe.height + PIPE_OFFSET);

    // Bottom pipe
    buffer_draw_rectangle(pipe_x, PIPE_OFFSET + pipe.height + PIPE_SEPARATION,
                          pipe_x + PIPE_WIDE_WIDTH, PIPE_OFFSET + pipe.height + PIPE_SEPARATION + PIPE_WIDE_HEIGHT);
    buffer_draw_rectangle(pipe_x + ((PIPE_WIDE_WIDTH - PIPE_NARROW_WIDTH) / 2), PIPE_OFFSET + pipe.height + PIPE_SEPARATION + PIPE_WIDE_HEIGHT + 1,
                          pipe_x + ((PIPE_WIDE_WIDTH - PIPE_NARROW_WIDTH) / 2) + PIPE_NARROW_WIDTH, DISPLAY_HEIGHT);
}

struct pipe_t _pipe_generate() {
    uint8_t rand_height = (get_rand_32() >> (uint32_t)(8 * 3)) / 255.0f * (PIPE_HEIGHT_MAX + 1);

    struct pipe_t pipe = {pipe_furthest_x, rand_height};
    pipe_furthest_x += (PIPE_SPACING * 1024);
    return pipe;
}