# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(flappy C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(flappy src/flappy.c
                src/display.c
                src/framebuffer.c
                src/game_engine.c
                src/input_handler.c
                src/player.c
                src/sprites.c
                src/pipe.c
            )

pico_set_program_name(flappy "flappy")
pico_set_program_version(flappy "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(flappy 1)
pico_enable_stdio_usb(flappy 0)

# Add the standard library to the build
target_link_libraries(flappy
        pico_stdlib
        pico_rand
        pico_time
        )

# Add the standard include files to the build
target_include_directories(flappy PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/src
)

# Add any user requested libraries
target_link_libraries(flappy 
        hardware_i2c
        )

pico_add_extra_outputs(flappy)

