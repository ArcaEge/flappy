#pragma once

// I2C
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

// Display
#define DISPLAY_I2C_ADDR 0x3C  // or 0x3D in some displays, depending on whether the D/C (Data/Command) pin is pulled HIGH or LOW
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_PAGE_COUNT (DISPLAY_HEIGHT / 8)  // 8 bits per byte
#define DISPLAY_PIXELS_PER_PAGE ((DISPLAY_WIDTH * DISPLAY_HEIGHT) / DISPLAY_PAGE_COUNT)
#define DISPLAY_BYTES_PER_PAGE (DISPLAY_PIXELS_PER_PAGE / 8)

// Input pin
#define INPUT_BUTTON_GPIO 6

// Game engine
#define GAME_ENGINE_TICKS_PER_SECOND 60
#define GAME_ENGINE_TICK_PERIOD (1000 / GAME_ENGINE_TICKS_PER_SECOND)  // Tick period in ms

// Player
#define PLAYER_DOWN_ACCELERATION 150  // Acceleration when velocity > 0
#define PLAYER_UP_ACCELERATION 500    // Acceleration when velocity < 0
#define PLAYER_JUMP_VELOCITY -3000
#define PLAYER_MAX_VELOCITY 3000
#define PLAYER_ANIMATION_FRAME_COUNT 3
#define PLAYER_ANIMATION_FRAME_LENGTH_TICKS 6

// Pipes
#define PIPE_NARROW_WIDTH 6             // Width of the narrow bit
#define PIPE_WIDE_WIDTH 8               // Width of the wide bit
#define PIPE_WIDE_HEIGHT 3              // Height of the wide bit
#define PIPE_SPACING DISPLAY_WIDTH / 3  // Distance between pipes
#define PIPE_SPEED 400
#define PIPE_SEPARATION 23
#define PIPE_NARROW_MIN_HEIGHT 3
#define PIPE_OFFSET (PIPE_WIDE_HEIGHT + PIPE_NARROW_MIN_HEIGHT + 1)
#define PIPE_HEIGHT_MAX (DISPLAY_HEIGHT - PIPE_SEPARATION - (2 * PIPE_OFFSET))