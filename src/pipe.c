#include "pipe.h"

int pipe_furthest_x = 0;
struct pipe_t pipes[PIPE_COUNT];

void pipe_initialise() {
}

void pipe_tick(uint64_t engine_tick_count, bool player_is_dead) {
    struct pipe_t pipe = {80 * 1024, PIPE_HEIGHT_MAX};
    _pipe_draw(pipe);
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