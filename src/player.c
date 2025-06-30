#include "player.h"

const int player_x_1024x = (DISPLAY_WIDTH / 4) * 1024;
int player_y_1024x = ((DISPLAY_HEIGHT / 2) - (PLAYER_HEIGHT / 2)) * 1024;
int player_velocity = 0;
bool player_is_dead = false;
bool player_activated = false;
uint64_t player_death_reset_timestamp = 0;

void player_tick(bool buttonPressed, uint64_t engine_tick_count) {
    uint8_t currentFrame = 1;

    if (!player_is_dead) {
        currentFrame = (engine_tick_count / PLAYER_ANIMATION_FRAME_LENGTH_TICKS) % (PLAYER_ANIMATION_FRAME_COUNT);

        if (player_activated) {
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
            } else if (player_y_1024x / 1024 > (int)PLAYER_MAX_Y) {
                _player_die();
            }
        } else if (buttonPressed) {
            player_activated = true;
            player_velocity = PLAYER_JUMP_VELOCITY;
        }
    } else {
        if (to_us_since_boot(get_absolute_time()) > player_death_reset_timestamp + PLAYER_DEATH_WAIT_TIME_US) {
            // Reset the chip (writing to raw register)
            *((volatile uint32_t*)(PPB_BASE + 0x0ED0C)) = 0x5FA0004;
        }

        if (player_y_1024x / 1024 < (int)PLAYER_MAX_Y) {
            if (player_velocity > 0)
                player_velocity += PLAYER_DOWN_ACCELERATION;
            else
                player_velocity += PLAYER_UP_ACCELERATION;
            player_y_1024x += player_velocity;
        } else {
            player_y_1024x = PLAYER_MAX_Y * 1024;
        }
    }

    if (buffer_write_bitmap(birdFrames[currentFrame], PLAYER_HEIGHT, player_x_1024x / 1024, player_y_1024x / 1024, false))
        _player_die();
}

void _player_die() {
    if (player_is_dead) return;
    player_death_reset_timestamp = to_us_since_boot(get_absolute_time());
    player_velocity = -PLAYER_DEATH_JUMP_VELOCITY;
    player_is_dead = true;
    printf("Player dead 💀💀\n");
}