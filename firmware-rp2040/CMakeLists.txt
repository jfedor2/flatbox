cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(flatbox)

pico_sdk_init()

add_executable(flatbox-rev4 src/flatbox.c)
target_include_directories(flatbox-rev4 PRIVATE src)
target_link_libraries(flatbox-rev4 pico_stdlib pico_stdlib tinyusb_device tinyusb_board)
target_compile_definitions(flatbox-rev4 PRIVATE FLATBOX_REV4)
pico_add_extra_outputs(flatbox-rev4)

add_executable(flatbox-rev5 src/flatbox.c)
target_include_directories(flatbox-rev5 PRIVATE src)
target_link_libraries(flatbox-rev5 pico_stdlib pico_stdlib tinyusb_device tinyusb_board)
target_compile_definitions(flatbox-rev5 PRIVATE FLATBOX_REV5)
pico_add_extra_outputs(flatbox-rev5)
