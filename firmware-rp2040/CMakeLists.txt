cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(flatbox)

pico_sdk_init()

add_executable(flatbox src/flatbox.c)

target_include_directories(flatbox PRIVATE src)

target_link_libraries(flatbox pico_stdlib pico_stdlib tinyusb_device tinyusb_board)

pico_add_extra_outputs(flatbox)
