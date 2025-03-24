# Flatbox: Low profile hitbox-layout fightstick

This repository contains 3D-printable models, PCB design files and code needed to make an arcade controller that looks like this:

![Assembled Flatbox](hardware-rev2/images/Flatbox-rev2b-finished-product.jpg)

There are seven major versions of the Flatbox. They all use Kailh low profile (choc v1) mechanical keyboard switches. The table below lists their main features. See the README for each version for details on how to make them.

version | case dimensions (mm) | compatibility | add-on board | onboard chip | SMT assembly required | firmware
------- | --------------- | ------------- | ------------ | ------------ | --------------------- | --------
[rev1.1](hardware-rev1.1) | 218x128x10 | PC, PS3 | Arduino Pro Micro | - | no | [ATmega32U4](firmware-atmega32u4)
[rev2](hardware-rev2) | 218x130x10 | PC, PS3 | - | ATmega32U4 | yes | [ATmega32U4](firmware-atmega32u4)
[rev3](hardware-rev3) | 218x130x10 | PC, PS3, PS4 or PC, Switch, PS3, PS4, PS5\* | [Brook PS3/PS4](https://www.brookaccessory.com/detail/58690501/) or [P5 mini](https://www.brookaccessory.com/detail/92299183/) | - | yes | [Brook](https://www.brookaccessory.com/download/)
[rev4.1](hardware-rev4.1) | 218x130x11 | PC, PS3, PS4\*, PS5\*, Switch | - | RP2040 | yes | [GP2040-CE](https://gp2040-ce.info/)
[rev5](hardware-rev5) | 218x126x10 | PC, PS3, PS4\*, Switch | [RP2040-Zero](https://www.waveshare.com/rp2040-zero.htm) | - | no | [GP2040-CE](https://gp2040-ce.info/)
[rev6](hardware-rev6) | 218x126x10 | PC, Switch | - | CH552T | yes | [CH552](firmware-ch552)
[rev7](hardware-rev7) | 218x130x11 | PC | [Xiao nRF52840](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html) | - | no | [slimbox-bt](https://github.com/jfedor2/slimbox-bt)

\* - with caveats
