/*
    Drives the SSD1306 display
    Most of the logic for this is from https://github.com/stlehmann/micropython-ssd1306
*/
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "defs.h"

#define DISPLAY_I2C_ADDR 0x3C // or 0x3D in some displays, depending on whether the D/C (Data/Command) pin is pulled HIGH or LOW
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

#define DISPLAY_STATE 0xAE
#define DISPLAY_SET_MEMORY_ADDRESS 0x20 // Send 0x00 after this to set to horizontal addressing mode
#define DISPLAY_START_LINE 0x40
#define DISPLAY_SEG_REMAP 0xA0
#define DISPLAY_SET_MUX_RATIO 0xA8
#define DISPLAY_COM_OUT_DIR 0xC0
#define DISPLAY_SET_OFFSET 0xD3
#define DISPLAY_SET_COM_PIN_CONFIG 0xDA // Send 0x12 after this for a 128x64 display
#define DISPLAY_SET_CLOCK_DIV 0xD5
#define DISPLAY_SET_PRECHARGE 0xD9
#define DISPLAY_SET_VCOM_DESELECT 0xDB
#define DISPLAY_SET_CONTRAST 0x81
#define DISPLAY_ENTIRE_ON 0xA4
#define DISPLAY_INVERTED_STATE 0xA6
#define DISPLAY_SET_CHARGE_PUMP 0x8D

void display_initialise();
void display_set_entire_screen_on_state(bool state);
void set_display_state(bool state);

int _display_write_command(uint8_t command);