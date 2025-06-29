#include "player.h"

const int player_x_1024x = (DISPLAY_WIDTH / 4) * 1024;
int player_y_1024x = ((DISPLAY_HEIGHT / 2) - (PLAYER_HEIGHT / 2)) * 1024;

int player_velocity = 0;

void player_tick(bool buttonPressed, uint64_t engine_tick_count) {
    uint8_t currentFrame = (engine_tick_count / PLAYER_ANIMATION_FRAME_LENGTH_TICKS) % (PLAYER_ANIMATION_FRAME_COUNT);
    
    if (player_velocity > 0)
        player_velocity += PLAYER_DOWN_ACCELERATION;
    else
        player_velocity += PLAYER_UP_ACCELERATION;

    if (player_velocity > PLAYER_MAX_VELOCITY) {
        player_velocity = PLAYER_MAX_VELOCITY;
    }

    if (buttonPressed) {
        player_velocity = PLAYER_JUMP_VELOCITY;
    }

    player_y_1024x += player_velocity;

    if (player_y_1024x / 1024 < PLAYER_MIN_Y) {
        player_y_1024x = PLAYER_MIN_Y * 1024;

        player_velocity = 0;
    }

    buffer_write_bitmap(birdFrames[currentFrame], PLAYER_HEIGHT, player_x_1024x / 1024, player_y_1024x / 1024, false);
}