# 32ch DMX LED Strip Dimmer

Arduino Mini and TLC4940 based 32 channel 12V PWM dimmer with [DMX512](https://en.wikipedia.org/wiki/DMX512) and [RDM](https://en.wikipedia.org/wiki/RDM_(lighting)) support.

## Table of contents
* [Features](#features)
* [Building and connecting the PCB](#building-and-connecting-the-pcb)
* [Installing the Software](#installing-the-software)
* [Setting the DMX channel](#setting-the-dmx-channel)
* [Write your own Software](#write-your-own-software)
* [Arduino Pin Configuration](#arduino-pin-configuration)
* [Contributing](#contributing)
* [See also](#see-also)
* [License](#license)

## Features
- 32 channels
- several amps current capability per channel
- high PWM frequency
- [DMX512](https://en.wikipedia.org/wiki/DMX512) with [RDM](https://en.wikipedia.org/wiki/RDM_(lighting)) support
- control LEDs, LED-Strips, Lamps, Motors, Relays, ...


## Building and connecting the PCB
The double sided PCB has surface mounted components on both sides. All resistors and capacitors are 0805 sized parts.
Screw terminals are available for all connections.

### Installing the Software

#### Connecting the Programmer
On the PCB, there is no dedicated programming connector. Instead, directly connect a serial adapter to the Arduino Pro Mini. Make sure that no DMX device is connected to the PCB.

#### Libraries
Install the required libraries within the Arduino IDE
* [tlc5940](https://github.com/PaulStoffregen/Tlc5940) Control of the two TLC5940 ICs
* [dmxserial2](https://github.com/mathertel/DmxSerial2) Used to handle DMX and RDM decoding

Open the [Sketch](dmx_led_strip_dimmer_32ch.ino) with the Arduino IDE, change the DMX address if needed, select the correct serial port and Hardware (Arduino Pro Mini or Arduino Mini) and click Upload.

### Setting the DMX channel
The DMX channel can be preset in the Arduino source code. Later, it can only be changed via RDM ([Remote Device Management](https://en.wikipedia.org/wiki/RDM_(lighting))) commands.

## Write your own Software
The PWM signals are created by two chained TLC5940 PWM LED drivers. Output 1-16 of U7 maps to Output 1-16 on the PCB, output 1-16 of U8 maps to Output 17-32 of the PCB. Per channel, one 74HC04 inverter is used. It is necessary because the PWM controller cannot completely turn off a directly connected N-channel MOSFET. It cannot get it's PWM count down to 0. By inverting the PWM signal, the PCB output can be turned off by fully turning on the TLC5940 channel.

### Arduino pin configuration

| Pin | Function              |
| --- | --------------------- |
|  0  | RxD (DMX)             |
|  1  | TxD (DMX)             |
|  2  | RS485 (DMX) Direction |
|  3  | GSCLK (TLC5940)       |
|  9  | XLAT (TLC5940)        |
| 10  | BLANK (TLC5949)       |
| 11  | SIN (TLC5940)         |
| 13  | SCLK (TLC5940)        |

Unlisted pins are not connected. The internal voltage regulator on the Arduino Mini Board is not used.

Take a look at the [schematic](schematic.pdf) too. It should clarify things further.

## Contributing
If you want to improve something, feel free to create a pull request.

One thing to optimize is the linear voltage regulator. Maybe someone is interested in fitting a suitable step down converter into the PCB?

## See also

* [TLC5940 datasheet](https://www.ti.com/lit/ds/symlink/tlc5940.pdf)
* [Wikipedia DMX512](https://en.wikipedia.org/wiki/DMX512)
* [Wikipedia RDM](https://en.wikipedia.org/wiki/RDM_(lighting))

## License
[MIT](https://choosealicense.com/licenses/mit/)
