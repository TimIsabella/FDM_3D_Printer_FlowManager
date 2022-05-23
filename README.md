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
precision of up to 6 digits beyond the decimal, which results in a measurement as low as 0.000001 MM.

This measurement is achieved by amplifying the minute differences by way of two long 
compound levers with small magnets attached at their ends, and analog hall effect sensors to
measure gauss intensity. The length of the levers dictates the precision (longer = more precise),
and doubling the levers at separate angles ensures accuracy by negating the oval circumfrance
which is common with filament.

![FlowManager1](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager1.jpg)
![FlowManager2](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager2.jpg)
![FlowManager3](https://github.com/TimIsabella/3D_Printer_Flow_Manager/blob/main/FlowManager3.jpg)
