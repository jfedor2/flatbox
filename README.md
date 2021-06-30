# Flatbox: Low profile hitbox-layout fightstick

This repository contains 3D-printable models, PCB design files and Arduino code needed to make an arcade controller that looks like this:

![Assembled Flatbox](hardware-rev2/images/Flatbox-rev2b-finished-product.jpg)

There are two versions of the Flatbox. They both use Kailh low profile (choc v1) mechanical keyboard switches. With [rev1](hardware-rev1) you solder an Arduino Pro Micro and the switches onto the board. With [rev2](hardware-rev2), there's no additional Arduino board, the microcontroller and the USB port are built into the main board (SMT assembly is required). See the README for each version for details on how to make them.

The included [firmware](firmware) is compatible with the PS3 and PC, though you can use other firmware if you want.
