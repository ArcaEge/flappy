#include "framebuffer.h"

uint8_t bufferPages[DISPLAY_PAGE_COUNT][DISPLAY_BYTES_PER_PAGE];

/// @brief Initialises the buffer
void buffer_initialise() {
    // Zero out the buffer. This isn't exactly needed as bufferPages is zeroed out already
    // when it is initialised, but it is still good to have.
    buffer_clear();
}

/// @brief Clears the buffer
void buffer_clear() {
    memset(bufferPages, 0x00, sizeof(uint8_t) * DISPLAY_BYTES_PER_PAGE * DISPLAY_PAGE_COUNT);
}

/// @brief Gets the state of the pixel at a coordinate from the buffer
/// @param x The x-value of the pixel, zero-indexed
/// @param y The y-value of the pixel, zero-indexed
/// @return State of the pixel: true if on, false if off
bool buffer_get_pixel_state(uint8_t x, uint8_t y) {
    uint8_t pageNo = _buffer_get_pixel_page_no(y);

    // x = column number
    uint8_t bitInByte = y % 8;  // (8 bits in a byte)
    uint8_t bitmask = 0b00000001 << bitInByte;
    return (bufferPages[pageNo][x] & bitmask) > 0;
}

/// @brief Sets the state of a pixel
/// @param x The x-value of the pixel, zero-indexed
/// @param y The y-value of the pixel, zero-indexed
/// @param state The state to set the pixel to: true if on, false if off
void buffer_set_pixel_state(uint8_t x, uint8_t y, bool state) {
    uint8_t pageNo = _buffer_get_pixel_page_no(y);

    // x = column number
    uint8_t bitInByte = y % 8;  // (8 bits in a byte)

    if (state) {
        uint8_t bitmask = 0b00000001 << bitInByte;
        bufferPages[pageNo][x] |= bitmask;
    } else {
        uint8_t bitmask = ~(0b00000001 << bitInByte);  // Invert bitmask
        bufferPages[pageNo][x] &= bitmask;
    }
}

/// @brief Write a bitmap to the framebuffer at specified x and y coordinates (only writes the white pixels). Bitmap must be 8 pixels wide
/// @param bitmap The pointer to the bitmap
/// @param height Height of the bitmap in pixels
/// @param x The x-coordinate to write the bitmap at, zero-indexed. Can be negative or greater than the display's width
/// @param y The y-coordinate to write the bitmap at, zero-indexed. Can be negative or greater than the display's height
/// @param erase If true, sets the pixels off instead of on
/// @returns Number of pixels that were already on (can be used for collision checking, returns zero if erase == true)
uint buffer_write_bitmap(uint8_t *bitmap, uint8_t height, int x, int y, bool erase) {
    uint pixels_already_on = 0;

    for (uint8_t bitmap_y = 0; bitmap_y < height; bitmap_y++) {
        // Check if it is within bounds of the display, ignore if otherwise
        if (y + bitmap_y < 0)
            continue;
        else if (y + bitmap_y >= DISPLAY_HEIGHT)
            break;

        for (uint8_t bitmap_x = 0; bitmap_x < 8; bitmap_x++) {
            // Check if it is within bounds of the display, ignore if otherwise
            if (x + bitmap_x < 0)
                continue;
            else if (x + bitmap_x >= DISPLAY_WIDTH)
                break;

            uint8_t bitmap_x_inverted = 7 - bitmap_x;

            // Get the value of the bitmap pixel
            uint8_t bitmask = 0b00000001 << bitmap_x_inverted;
            bool pixel_is_on = (bitmap[bitmap_y] & bitmask) > 0;

            if (pixel_is_on) {
                if (!erase) pixels_already_on += buffer_get_pixel_state(x + bitmap_x, y + bitmap_y);

                buffer_set_pixel_state(x + bitmap_x, y + bitmap_y, !erase);
            }
        }
    }

    return pixels_already_on;
}

/// @brief Draws a rectangle to the framebuffer. X-values can be outside the display's range
/// @param x1 Lower x-value, inclusive
/// @param y1 Lower y-value, inclusive
/// @param x2 Higher x-value, exclusive
/// @param y2 Higher y-value, exclusive
void buffer_draw_rectangle(int x1, int y1, int x2, int y2) {
    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2 && x < DISPLAY_WIDTH; x++) {  // Break if the x-value is outside the display
            if (x < 0) continue;                              // Skip if x is too far left

            buffer_set_pixel_state(x, y, true);
        }
    }
}

/// @brief Converts a pixel's y-value to the page that it is in
/// @param y The y-value of the pixel
/// @return The index of the page that the pixel is in
uint8_t _buffer_get_pixel_page_no(uint8_t y) {
    return y / 8;  // 8 bits in a byte
}