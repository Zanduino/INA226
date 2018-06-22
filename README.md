# INA226 - Has been merged into a new library [INA](https://github.com/SV-Zanshin/INA) 
## This library has been deprecated and is obsolete
Further development and bug fixes will be done in the new [INA](https://github.com/SV-Zanshin/INA)  library.    
<img src="https://github.com/SV-Zanshin/INA226/blob/master/Images/INA226.jpg" width="175" align="right"/>
    
The new [INA](https://github.com/SV-Zanshin/INA) library along with the associated example programs and documentation at https://github.com/SV-Zanshin/INA/wiki supports multiple devices of multiple types in one combined library. The INA226 library functions have been duplicated in the new INA library and several additional functions have been incorporated as well. In addition, several minor bugs were detected and fixed during the transition to the new library.

## Original page follows:
INA226 High-Side/Low-Side Bi-Directional I2C Current and Power Monitor library for the _Arduino_.  Texas Instruments produces this family of power monitors and the series is described at on their product page at [INA226](http://www.ti.com/product/INA226).
## INA219 vs INA226
Several breakout boards, tutorials and libraries exist for the INA219, which is the "little brother" to this INA226 chip. While the pin 
layout is similar, with the INA219 having 8 pins and the INA226 having 2 more pins, the internal configuration settings and registers are 
different and require the functions and methods in this library to access.
## Hardware layout
The [datasheet](http://www.ti.com/lit/ds/symlink/ina226.pdf) has examples of how to hook up INA226. The package is a small VSSOP and I used a blank breakout board, some solder paste, a frying pan, desoldering braid, a magnifying glass and quite a bit of time to set up the first breadboard example. I've since seen breakout boards available on the web but since only a few external components are necessary apart from connecting the 10 pins of the INA226 I'll remain with self-build.
## Library description
The library locates all INA226 devices on the I2C chain. Each unit can be individually configured with 4 setup parameters describing the expected voltage, shunt / resistor values which then set the internal configuration registers is ready to begin accurate measurements.  The details of how to setup the library along with all of the publicly available methods can be found on the [INA226 wiki pages](https://github.com/SV-Zanshin/INA226/wiki).
Great lengths have been taken to avoid the use of floating point in the library. To keep the original level of precision without loss but to allow the full range of voltages and amperes to be returned the amperage results are returned as 32-bit integers.

The INA226 has a dedicated interrupt pin which can be used to trigger pin-change interrupts on the Arduino and the examples contain a program that measures readings using this output pin so that the Arduino can perform other concurrent tasks while still retrieving measurements.

![Zanshin Logo](https://www.sv-zanshin.com/r/images/site/gif/zanshinkanjitiny.gif) <img src="https://www.sv-zanshin.com/r/images/site/gif/zanshintext.gif" width="75"/>
