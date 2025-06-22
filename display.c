#include "display.h"

/// @brief Initialises the screen
void display_initialise() {
    printf("--- Initialisation ---\n");

    int res = _display_write_command(DISPLAY_STATE | 0);
    printf("Display off: %d\n", res);

    res = _display_write_command(DISPLAY_SET_MEMORY_ADDRESS);
    printf("res: %d\n", res);
    res = _display_write_command(0x00);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_START_LINE | 0x00);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SEG_REMAP | 0x01);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_MUX_RATIO);
    printf("res: %d\n", res);
    res = _display_write_command(DISPLAY_HEIGHT - 1);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_COM_OUT_DIR | 0x08);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_OFFSET);
    printf("res: %d\n", res);
    res = _display_write_command(0x00);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_COM_PIN_CONFIG);
    printf("res: %d\n", res);
    res = _display_write_command(0x12);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_CLOCK_DIV);
    printf("res: %d\n", res);
    res = _display_write_command(0x80);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_PRECHARGE);
    printf("res: %d\n", res);
    res = _display_write_command(0xF1);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_VCOM_DESELECT);
    printf("res: %d\n", res);
    res = _display_write_command(0x30);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_CONTRAST);
    printf("res: %d\n", res);
    res = _display_write_command(0xFF);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_ENTIRE_ON | 1);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_INVERTED_STATE | 0);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_SET_CHARGE_PUMP);
    printf("res: %d\n", res);
    res = _display_write_command(0x14);
    printf("res: %d\n", res);

    res = _display_write_command(DISPLAY_STATE | 1);
    printf("Display on: %d\n", res);
}

/// @brief Sets the entire screen on or equal to previous state
/// @param state State of the Entire Screen ON register; if true the entire screen is on, else it is normal (i.e. equal to the previous state)
void display_set_entire_screen_on_state(bool state) {
    int res = _display_write_command(DISPLAY_ENTIRE_ON | (uint8_t)state);
}

/// @brief Sets the state of the screen
/// @param state State of the screen
void set_display_state(bool state) {
    int res = _display_write_command(DISPLAY_STATE | (uint8_t)state);
}

int _display_write_command(uint8_t command) {
    uint8_t data[] = {0x80, command};
    return i2c_write_blocking(I2C_PORT, DISPLAY_I2C_ADDR, data, 2, false);
}