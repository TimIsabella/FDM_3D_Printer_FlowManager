# 3D Printer Flow Manager

Possibly the biggest issue in FDM 3D printing is flow control, and the reasons for this is as follows:
- Inconsistent filament diameter
- Improperly calibrated flow rate
- Extruder skipping

Any one of these can cause bad prints or failed prints, which is costly in material and time.

Flow Manager is an attempt to control all three of these critical parameters, and in addition will yeild 
consitent layers which means better looking and performing prints.

## How?
By measuring the filament diameter as it is fed, an exact flow rate can be calculated to ensure
a consistent flow. Flow Manager measures this filament diameter by three points evenly offset 
around the circumfrance of the filament (offset as a trinagle), and averaging those points with a 
precision of up to 6 digits beyond the decimal, which results in a measurement sensativity 
as low as 0.000001mm, and a filament diameter as small as 1mm.

This measurement is achieved by amplifying the minute differences by way of two long 
compound levers with small magnets attached at their ends, and analog hall effect sensors to
measure gauss intensity. The length of the levers dictates the precision (longer = more precise),
and doubling the levers at separate angles ensures accuracy by negating the oval circumfrance
which is common with filament.

In addition to diameter measurement, a digital encoder wheel can be placed as the third point of
contact separate from the lever wheels to precicely measure flow, including retracts, priming, and run-out.

## Future Work?
Production for this project stopped in early 2020. Although the diameter measurement function
performed far better than I ever anticipated, I ran into the issue 

## Parts needed
- Printed model (see repo)
- Arduino Nano (5v)
- 2x 11mm X 7mm X 3mm ball bearings
- 2x 8mm X 14mm X 4mm ball bearings
- 1x HK0306 drawn cup needle bearing, 3mm bore, 6.5mm OD, 6mm width
- 2x 0.5mm X 3mm X 10mm compresson springs
- 2x 4mm X 2mm round magnets
- 2x A1302 Continuous-Time Ratiometric Linear Hall-Effect Sensors (5v)
- 1x ESP8266 Module. You will also need a flash tool and flash module to proram the ESP8266 (there is lots of documentaion online). CAUTION: the ESP8266 module is 3.6v, so the voltage must be managed from the 5v off of the Arduino Nano board.
- Assorted resistors and wires set

- OPTIONAL: KY-040 Rotary Encoder Module (untested). This is what I was goig to use to measure the flow rate,
although it was never implimented.

![FlowManager1](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager1.jpg)
![FlowManager2](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager2.jpg)
![FlowManager3](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager3.jpg)
