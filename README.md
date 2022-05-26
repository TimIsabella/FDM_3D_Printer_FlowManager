# 3D Printer Flow Manager

Possibly the biggest issue in FDM 3D printing is flow control, and the reasons for this is as follows:
- Inconsistent filament diameter
- Improperly calibrated flow rate
- Extruder skipping

Any one of these can cause bad prints or failed prints, which is both costly in material and time.

Flow Manager is an attempt to control all three of these critical parameters, and in addition will yield 
consistent layers which means better looking and better performing prints.

## How?
By measuring the filament diameter as it is fed, an exact flow rate can be calculated to ensure
a consistent flow. Flow Manager measures this filament diameter by three points offset around
the circumference of the filament (offset as a triangle), and averaging those points with a 
precision of up to 6 digits beyond the decimal, which results in a measurement sensitivity 
as low as 0.000001mm, and a filament diameter as small as 1mm.

This measurement is achieved by amplifying the minute movements by way of dual single levers set with
high fulcrum points, and small magnets inlaid at their ends. These magnets are positioned over
highly sensitive linear hall effect sensors which measure distance by magnetic Gauss intensity. 
The length of the levers dictate the precision (longer = more precise), while canting the lever wheels at 
opposing angles ensures accuracy by simultaneously measuring at two separate points, which also negates the 
oval circumference shape which is common with filament.

In addition to diameter measurement, a digital encoder wheel can be placed as a third point of
contact separate from the lever wheels, to precisely measure overall filament movement, including retracts,
priming, skipping, jamming, and run-out.

This measurement is then sent by serial to the ESP8266 module that contains a small webserver that wirelessly
transmits g-code commands to any WiFi enabled 3D printer, continuously adjusting the flow rate live.

Theoretically, with the precise inclusion of the encoder wheel combined with diameter measurements, the exact
length to the nozzle tip can be offset with near perfect extrusion precision, making literally any FDM 3D printer
capable of detailed prints previously unheard of while also eliminating failures.

## Future Work?
Production for this project stopped in early 2020. Although the diameter measurement function
performed far better than I ever anticipated, I ran into difficulty with proprietary communication
methods for different printer manufacturers, therefore this project would probably be best suited on a
Raspberry PI board and connected to the OctoPrint platform.

Moreover, it may be possible to source a linear hall effect sensor that runs on 3v which can be connected
directly to the two I/O ports of the ESP8266, and the board flashed with all code necessary using MicroPython,
which would eliminate the need for the Nano board alltogether and vastly simplify the entire unit.

## Parts List
- Printed model (see repo .STL files, or .MQO for Metasequoia), 0.4mm nozzle at a minimum, shell is best printed upright.
- Arduino Nano (5v)
- 2x 11mm X 7mm X 3mm ball bearings
- 2x 8mm X 14mm X 4mm ball bearings
- 1x HK0306 drawn cup needle bearing, 3mm bore, 6.5mm OD, 6mm width
- 2x 0.5mm X 3mm X 10mm compression springs
- 2x 4mm X 2mm round magnets
- 2x A1302 Continuous-Time Ratiometric Linear Hall-Effect Sensors (5v)
- Assorted resistors and wires set
- 1x ESP8266 ESP-01 Module. You will also need a flash tool and flash module to program the ESP8266 (there is lots of documentation online). CAUTION: the ESP8266 module is 3.6v max, so do not connect to the 5v pin on the Arduino Nano or you will destroy the ESP8266. The Arduino Nano does however have a pin for 3.3v, which powers the ESP8266 just fine.

- OPTIONAL: KY-040 Rotary Encoder Module (untested). This is what I was going to use to measure the filament movement,
although it was never implemented. Essentially this encoder would be attached to a wheel that rotates with the
movement of the filament, and calculated along with measurement.

![FlowManager1](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager1.jpg)
![FlowManager2](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager2.jpg)
![FlowManager3](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager3.jpg)
![Wiring](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/Arduino%20Nano%20to%20ESP8266%20wiring.jpg)

## Screenshots from Version 11 (see .MQO file)
![FlowManager11](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/Version%2011-1.png)
![FlowManager11](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/Version%2011-2.png)
![FlowManager11](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/Version%2011-3.png)
