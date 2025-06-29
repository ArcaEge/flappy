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
void buffer_clear();
bool buffer_get_pixel_state(uint8_t x, uint8_t y);
void buffer_set_pixel_state(uint8_t x, uint8_t y, bool state);
void buffer_draw_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
uint buffer_write_bitmap(uint8_t *bitmap, uint8_t height, int x, int y, bool erase);

uint8_t _buffer_get_pixel_page_no(uint8_t y);