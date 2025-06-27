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
#define GAME_ENGINE_TICKS_PER_SECOND 20
#define GAME_ENGINE_TICK_PERIOD (1000 / GAME_ENGINE_TICKS_PER_SECOND)   // Tick period in ms