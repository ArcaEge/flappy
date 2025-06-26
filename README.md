# Flappy bird on a Pi Pico

Flappy bird on a Pi Pico 2 written in C, with the goal of writing it in ARM assembly in the future. Uses an SSD1306 display and doesn't use any libraries other than the Pico SDK.

## Pinout

| Pi Pico pin | Connected to |
| ------------|--------------|
| GPIO 4      | SSD1306: SDA |
| GPIO 5      | SSD1306: SCL |
| 3.3V        | SSD1306      |
| GND         | SSD1306      |
| 3.3V        | PTM switch   |
| GPIO 6      | PTM switch   |

The switch is pulled down internally using the internal pull-downs of the Pico.
