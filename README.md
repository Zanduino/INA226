# INA226
INA226 High-Side/Low-Side Bi-Directional I2C Current and Power Monitor library for the _Arduino_
## INA219 vs INA226
Several breakout boards, tutorials and libraries exist for the INA219, which is the "little brother" to this INA226 chip. While the pin 
layout is similar, with the INA219 having 8 pins and the INA226 having 2 more pins, the internal configuration settings and registers are 
different and require the functions and methods in this library to access.
## Hardware layout
The [datasheet](http://www.ti.com/lit/ds/symlink/ina226.pdf) has examples of how to hook up INA226. The package is a small VSSOP and I used
a blank breakout board, some solder paste, a frying pan, desoldering braid, a magnifying glass and quite a bit of time to set up the first
breadboard example.
## Library description
The library will find the INA226 on the I2C chain and with 4 setup parameters describing the expected voltage, shunt / resistor values the
internal configuration registers will be set and the library is ready to begin very accurate measurements.  The details of how to setup
the library along with all of the publicly available methods can be found on the [INA226 wiki pages](https://github.com/SV-Zanshin/INA226/wiki)

![Zanshin Logo](https://www.sv-zanshin.com/images/gif/zanshinkanjitiny.gif) <img src="https://www.sv-zanshin.com/images/gif/zanshintext.gif" width="75"/>
