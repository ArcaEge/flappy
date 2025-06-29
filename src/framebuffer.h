/*
    Memory efficient framebuffer logic
*/
#pragma once
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "display.h"

extern uint8_t bufferPages[DISPLAY_PAGE_COUNT][DISPLAY_BYTES_PER_PAGE];

void buffer_initialise();
bool buffer_get_pixel_state(uint8_t x, uint8_t y);
void buffer_set_pixel_state(uint8_t x, uint8_t y, bool state);
uint buffer_write_bitmap(uint8_t *bitmap, uint8_t height, int x, int y, bool erase);

uint8_t _buffer_get_pixel_page_no(uint8_t y);