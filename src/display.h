/*
    Drives the SSD1306 display
    Most of the logic for this is from https://github.com/stlehmann/micropython-ssd1306
*/
#pragma once
#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include "defs.h"

#define DISPLAY_STATE 0xAE
#define DISPLAY_SET_MEMORY_ADDRESSING_MODE 0x20  // Send 0x01 after this to set to vertical addressing mode
#define DISPLAY_START_LINE 0x40
#define DISPLAY_SEG_REMAP 0xA0
#define DISPLAY_SET_MUX_RATIO 0xA8
#define DISPLAY_COM_OUT_DIR 0xC0
#define DISPLAY_SET_OFFSET 0xD3
#define DISPLAY_SET_COM_PIN_CONFIG 0xDA  // Send 0x12 after this for a 128x64 display
#define DISPLAY_SET_CLOCK_DIV 0xD5
#define DISPLAY_SET_PRECHARGE 0xD9
#define DISPLAY_SET_VCOM_DESELECT 0xDB
#define DISPLAY_SET_CONTRAST 0x81
#define DISPLAY_ENTIRE_ON 0xA4
#define DISPLAY_INVERTED_STATE 0xA6
#define DISPLAY_SET_CHARGE_PUMP 0x8D
#define DISPLAY_SET_COLUMN_ADDRESS 0x21
#define DISPLAY_SET_PAGE_ADDRESS 0x22

void display_initialise();
void display_set_entire_screen_on_state(bool state);
void set_display_state(bool state);
void display_write(uint8_t framebuffer[DISPLAY_PAGE_COUNT][DISPLAY_BYTES_PER_PAGE]);

int _display_write_command(uint8_t command);
void _display_write_data(uint8_t displayData[DISPLAY_PAGE_COUNT][DISPLAY_BYTES_PER_PAGE]);