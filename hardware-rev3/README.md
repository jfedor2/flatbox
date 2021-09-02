# Flatbox rev3

This is rev3 of the Flatbox. In this version the PCB only includes a USB port and you solder a [Brook PS3/PS4 fighting board PCB](https://www.brookaccessory.com/detail/58690501/) onto it (the small 40x40mm one). That way you get PS4 compatibility.

To make one you will need:

* [Brook PS3/PS4 fighting board PCB](https://www.brookaccessory.com/detail/58690501/)
* [3D printed case parts](3d-printed-case) - top and bottom
* [the Flatbox PCB](pcb)
* 12x Kailh low profile (choc v1) switches of your choice
* (optionally) 12x Kailh low profile hotswap sockets
* [3D printed buttoncaps](../3d-printed-buttoncaps)
* 6x 6x6x5mm tact switches
* 7x 3x10mm wood screws
* some kind of rubber feet or non-slip padding for the bottom
* a soldering iron

I printed the case at 0.20mm layer height. The top part should be printed upside-down, the bottom part should be printed as-is. They don't require supports.

I used [JLCPCB](https://jlcpcb.com/) to make the PCB and assemble the SMD parts. The [included files](pcb) can be used with JLCPCB directly. If you want to use some other service, check the file formats that they expect. When ordering from JLCPCB, upload the Gerber zip, leave all the settings at default (you can choose the PCB color), then select "SMT Assembly" and upload the BOM and CPL files. PCB thickness should be 1.6mm.

The PCB you get from JLCPCB will look like this:

![Flatbox rev3 PCB with SMD parts assembled](images/Flatbox-rev3-pcb-with-smd-parts.jpg)

The switches can be soldered in directly to the PCB or you can use hotswap sockets. If you want to use hotswap sockets, you will have to print the appropriate bottom part of the case (it's 1mm thicker).

The Brook board has to be soldered directly on top of the PCB, otherwise it won't fit in the case (the plastic base of the pin header can't go between the Brook board and the PCB).

Since this version uses a Brook board, it doesn't use my firmware or any open source firmware, go to [Brook's website](https://www.brookaccessory.com/download/PS3/) for firmware updates.

![Flatbox rev3 Brook board soldered onto the PCB](images/Flatbox-rev3-brook-board-soldered.jpg)

![Flatbox rev3 exploded view of the 3D printed case](images/Flatbox-rev3-exploded.png)

PCB design licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).

PCB design uses the following libraries:

* [keyswitches.pretty](https://github.com/daprice/keyswitches.pretty) by [daprice](https://github.com/daprice) ([CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/))
* [Type-C.pretty](https://github.com/ai03-2725/Type-C.pretty) by [ai03-2725](https://github.com/ai03-2725)
