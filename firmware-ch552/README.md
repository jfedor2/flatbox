This is gamepad firmware that runs on the CH552T chip. It works with Flatbox [rev6](../hardware-rev6).

It is a minor modification of Stefan Wagner's [CH552-MouseWiggler](https://github.com/wagiminator/CH552-MouseWiggler).

To compile the firmware you need the `sdcc` compiler. To flash the firmware you need the `pyusb` Python module.

To build the firmware, run `make bin`.

To build and flash the firmware onto a board, hold the "BOOT" button while plugging the board into your computer, then run `make flash` immediately after.

To flash an existing binary, hold the "BOOT" button while plugging the board into your computer, then run `python3 tools/chprog.py gamepad.bin` immediately after.
