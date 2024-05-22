# Flatbox rev6

This is rev6 of the Flatbox. In this version the PCB includes a microcontroller and USB port. Everything is built in, you only have to add the switches (and flash the firmware).

To make one you will need:

* [3D printed case parts](3d-printed-case) - top and bottom
* [the PCB](pcb)
* 12x Kailh low profile (choc v1) switches of your choice
* (optionally) 12x Kailh low profile hotswap sockets
* [3D printed buttoncaps](../3d-printed-buttoncaps)
* 2x 6x6x5mm tact switches
* 7x M3x6 flat head (countersunk) screws
* (optionally) 5x M2x4 screws to secure the PCB to the case
* some kind of rubber feet or non-slip padding for the bottom
* a soldering iron

I printed the case at 0.20mm layer height. The top part should be printed upside-down, the bottom part should be printed as-is. They don't require supports.

I used [JLCPCB](https://jlcpcb.com/) to make the PCB and assemble the SMD parts. The [included files](pcb) can be used with JLCPCB directly. If you want to use some other service, check the file formats that they expect. When ordering from JLCPCB, upload the Gerber zip, leave all the settings at default (you can choose the PCB color), then select "SMT Assembly" and upload the BOM and CPL files. PCB thickness should be 1.6mm.

The PCB you get from JLCPCB will look like this:

![Flatbox rev6 PCB with SMD parts assembled](images/Flatbox-rev6-pcb-with-smd-parts.jpg)

The switches can be soldered in directly to the PCB or you can use hotswap sockets. If you want to use hotswap sockets, you will have to print the appropriate bottom part of the case (it's 1mm thicker).

See [here](../firmware-ch552) for firmware information.

![Flatbox rev6 exploded view of the 3D printed case](images/Flatbox-rev6-exploded.png)

PCB design licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).

PCB design uses the following libraries:

* [keyswitches.pretty](https://github.com/daprice/keyswitches.pretty) by [daprice](https://github.com/daprice) ([CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/))
* [Type-C.pretty](https://github.com/ai03-2725/Type-C.pretty) by [ai03-2725](https://github.com/ai03-2725)
