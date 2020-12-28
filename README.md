# IR_dump

## Abstract
IR_dump should help you to analyze IR communication between remote-controls and devices.
It detects IR commuication within reach and decodes the IR commands and IR protocols. This data could be used to detect error or interact with IR devives by transfering the codes to your own projects.

## Hardware
The wiring definded in this sketch is for a  [M5Stack atom lite microcontroller](https://m5stack.com/products/atom-lite-esp32-development-kit) based on a ESP32 pico. The atom lite provides a grove connector where the [M5Stack Mini Infrared Emitter & Receiver Unit](https://m5stack.com/collections/m5-unit/products/ir-unit) can be connected without soldering or using breadboards. Please adapt this sketch for your controller and IR setup if needed.

![Hardware Scheme](https://github.com/mlaber/ir_dump/blob/main/ir_dump_scheme.jpg)

## Usage
Import the code to arduino add [IRremote Library](https://github.com/z3t0/Arduino-IRremote)with arduino library manager. And upload the code to the micro-controller. After a reset open the Serial monitor from arduino tools menu with 115200 baud.
Now point with your remote to the IR unit and push a single button on the remote, you should now able to see the protocol and the codes.

![Serial Monitor example](https://github.com/mlaber/ir_dump/blob/main/screenshot_serial_monitor.png)

### NOTES
Using the [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) Library by Ken Shirriff http://www.righto.com Copyright (c) 2016 Rafi Khan Copyright (c) 2020 Armin Joachimsmeyer
