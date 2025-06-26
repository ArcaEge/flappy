#include "display.h"

/// @brief Initialises the screen
void display_initialise() {
    printf("--- Initialisation ---\n");

    int res = _display_write_command(DISPLAY_STATE | 0);
    printf("I2C connection succeeded: %s\n", res >= 0 ? "yes" : "no");

    // Set to horizontal addressing mode
    _display_write_command(DISPLAY_SET_MEMORY_ADDRESSING_MODE);
    _display_write_command(0x00);

    _display_write_command(DISPLAY_START_LINE | 0x00);

    _display_write_command(DISPLAY_SEG_REMAP | 0x01);

    _display_write_command(DISPLAY_SET_MUX_RATIO);
    _display_write_command(DISPLAY_HEIGHT - 1);

    _display_write_command(DISPLAY_COM_OUT_DIR | 0x08);

    _display_write_command(DISPLAY_SET_OFFSET);
    _display_write_command(0x00);

    _display_write_command(DISPLAY_SET_COM_PIN_CONFIG);
    _display_write_command(0x12);

    _display_write_command(DISPLAY_SET_CLOCK_DIV);
    _display_write_command(0x80);

    _display_write_command(DISPLAY_SET_PRECHARGE);
    _display_write_command(0xF1);

    _display_write_command(DISPLAY_SET_VCOM_DESELECT);
    _display_write_command(0x30);

    _display_write_command(DISPLAY_SET_CONTRAST);
    _display_write_command(0xFF);

    _display_write_command(DISPLAY_ENTIRE_ON | 0);

    _display_write_command(DISPLAY_INVERTED_STATE | 0);

    _display_write_command(DISPLAY_SET_CHARGE_PUMP);
    _display_write_command(0x14);

    _display_write_command(DISPLAY_STATE | 1);
}

/// @brief Sets the entire screen on or equal to previous state
/// @param state State of the Entire Screen ON register; if true the entire
/// screen is on, else it is normal (i.e. equal to the previous state)
void display_set_entire_screen_on_state(bool state) {
    int res = _display_write_command(DISPLAY_ENTIRE_ON | (uint8_t)state);
}

/// @brief Sets the state of the screen
/// @param state State of the screen
void set_display_state(bool state) {
    int res = _display_write_command(DISPLAY_STATE | (uint8_t)state);
}

/// @brief Writes the contents of the framebuffer to the screen
/// @param framebuffer The framebuffer containing the data
void display_write(uint8_t framebuffer[DISPLAY_PAGE_COUNT][DISPLAY_BYTES_PER_PAGE]) {
    // Set column range to include all columns
    _display_write_command(DISPLAY_SET_COLUMN_ADDRESS);
    _display_write_command(0x00);
    _display_write_command(DISPLAY_WIDTH - 1);

    // Set page range to include all pages
    _display_write_command(DISPLAY_SET_PAGE_ADDRESS);
    _display_write_command(0x00);
    _display_write_command(DISPLAY_PAGE_COUNT - 1);

    _display_write_data(framebuffer);
}

int _display_write_command(uint8_t command) {
    uint8_t data[] = {0x80, command};
    return i2c_write_blocking(I2C_PORT, DISPLAY_I2C_ADDR, data, 2, false);
}

void _display_write_data(uint8_t displayData[DISPLAY_PAGE_COUNT][DISPLAY_BYTES_PER_PAGE]) {
    uint8_t display_start_line = 0x40;
    i2c_write_burst_blocking(I2C_PORT, DISPLAY_I2C_ADDR, &display_start_line, 1);
    i2c_write_blocking(
        I2C_PORT, DISPLAY_I2C_ADDR, &displayData[0][0],
        DISPLAY_PAGE_COUNT * DISPLAY_BYTES_PER_PAGE, false);
}