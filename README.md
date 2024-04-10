# Trim Wheel for Microsoft Flight Simulator 2020

##### Version: 1.0
##### License: MIT
##### Author: Albert J. Fernandez | 04-2024
##### https://github.com/ajfdez/TrimWheel


## DESCRIPTION

This is a code for a hardware trim wheel controller for Microsoft Flight Simulator 2020 using SPAD.neXt and an Arduino UNO or Leonardo like board.

<img src="https://github.com/ajfdez/TrimWheel/blob/main/img/TrimWheel-BOD.png" width="397" height="526">



Even the most el cheapo encoder found on Amazon will perform much more better than those used in the Saitek/Logitech hardware controllers. 
Look for "rotary encoder" on Amazon or your electronics parts supplier to find yours.
This code uses hardware interrupts for not loosing a single rotary step, Allowing for better simulation inmersion and accuracy with a tactile feedback control.

The trim wheel is a simple rotary encoder used to control the trim wheel in the simulator. 
The Arduino board is connected to the PC via USB and the SPAD.neXt software is used to communicate with the Arduino board.

SPAD.neXt is a software that allows you to create custom controls for flight simulators. You can download it from https://www.spadnext.com/. 
A license for running SPAD.next is needed, and charges may apply.

This project is not endorsed or afiliated in any way with SPAD.next.


## CODE COMPILATION          

This code is compiled using Visual Studio Code and PlatformIO Extension Core 6.1.14 Home 3.4.4 versions.

It can also be compiled using the Arduino IDE changing the extension from main.cpp to main.ino, or copy/pasting the code into the Arduino IDE.


## HARDWARE

1   Arduino Uno/Leonardo/Mega board.

1   Rotary encoder with or without push button. Look for "rotary encoder" on Amazon or your electronics parts supplier. 
    Just about any will work, for best results look for one with a PCB and a knob. The PCB marked pins usually are:

|   PIN    | Connection                                                 |
|----------|------------------------------------------------------------|
|    GND   | Ground connection to Arduino GND pin.                      |
|     +    | 5V power supply. See NOTE 1.                               |
|    SW    | Push button. Not used.     |
|    DT    | Encoder pin B to Arduino Pin 2. See NOTE 2.                |
|    CLK   | Encoder pin A to Arduino Pin 3. See NOTE 2.                |

#### NOTE 1: + or 5V pin of the encoder PCB is used for the included pull up resistors for the encoder pins A and B, since we are using the pull up resistors embedded in the Arduino chip, this pin is not needed, and may left unconnected. But if you are experiencing "lost ticks", or using long cables from Arduino to encoder boards, this pin may need be used for better rotary detection.

#### NOTE 2: The Encoder pins A and B can be reversed to Arduino Pin 3 and 2 to follow your CW/CCW trim setup.

1   Led any color you like. Optional, you can use the Arduino Pin 13 led if you preffer.

1   150 Ohm 1/4w resistor. Optional, only needed if an external led is used. 
    This is a standard value for 5 volts powered leds. This value may be changed according to the used led power needs using Ohm's law.


## HARDWARE SETUP          

Arduino UNO or Leonardo like board, a rotary encoder and a push button.

The rotary encoder pins DT and CLK are connected to Pin 2 and Pin 3 of the Arduino board. The GND Pin goes to any Arduino GND pin.

The connection stablished led is connected to Pin 12 via a 150 Ohm resistor. 
Completely optional, lits up when a SPAD.next connection is up and running. You can even use the Arduino board led using the Pin 13, changing the ledPin variable to 13.


## WIRING

Take a look in the /img folder for the images of the circuit.

<img src="https://github.com/ajfdez/TrimWheel/blob/main/img/TrimWheel-SCH.png" width="397" height="526">

## SPAD.neXt

The SPAD.neXt configuration is very simple, just create a new device in the settings page, then add a "Serial Device" and select the Arduino board COM port from the list.

The config is DTR off, 32 bit ON. 

SPAD.next needs to be restarted after this settings.


## CREDITS

SPAD.next  https://www.spadnext.com/

This code uses the CmdMessenger and EncoderButton libraries.

You can install them using the PlatformIO Library Manager or the Arduino Library Manager.
                                  
- CmdMessenger by Thijse. https://github.com/thijse/Arduino-CmdMessenger
                  
- EncoderButton by Stutchbury. https://github.com/Stutchbury/EncoderButton

