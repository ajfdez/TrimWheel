/*******************************************************************
* Project           : Trim Wheel_FS20
* Version           : 1.0
* License           : MIT
* Author            : Albert J. Fdez.
* Date              : 07/APR/2024
*
* Description       : This code facilitates the creation of an external trim wheel controller for Microsoft Flight Simulator 2020 using SPAD.neXt and an Arduino UNO
*                     or Leonardo like board.
*                     The controller employs a simple rotary encoder to adjust the simulator's trim wheel, enhancing the realism and precision of flight control. 
*                     The Arduino board is connected to the PC via USB and the SPAD.neXt software is used to communicate with the Arduino board.
*                     SPAD.neXt is a software that allows you to create custom controls for flight simulators. You can download it from https://www.spadnext.com/.
*                     See readme.md for more information.
*
* Dependencies      : See readme.md
*                    
*
* Compilation       : See readme.md
*
* Revision History  :
* Date		    Author 			    Comments
* ------------------------------------------------------------------
* 07/04/2024	Albert J. Fdez	Initial version.
*
*/

#include <CmdMessenger.h>  
#include <EncoderButton.h>

// Create an encoder button object, Encoder Pin A, Encoder Pin B, Encoder Button Pin. 
// Reverse the encoder direction reversing Pin A and Pin B if needed.
// The encoder button is optional and is not used here, if you don't have a button, just use EncoderButton eb1(3, 2);
EncoderButton eb1(3, 2, 4); 

// Create a CmdMessenger object
CmdMessenger messenger(Serial);

// Connection stablished led Pin. You can change this to Pin 13 if you are using a Arduino Uno or equivalent and want to use the onboard led.
int conLed = 12;

// List of commands that this app supports
enum
{
  kRequest = 0, // Request from SPAD.neXt
  kCommand = 1, // Command to SPAD.neXt
  kEvent = 2, // Events from SPAD.neXt
  kDebug = 3, // Debug strings to SPAD.neXt Logfile
  kSimCommand = 4, // Send Event to Simulation
};


// ------------------  C A L L B A C K S -----------------------

void onEvent()
{
  char *szRequest = messenger.readStringArg();

  // Connection stablished
  if (strcmp(szRequest, "START") == 0) {
      digitalWrite(conLed, true);                   
      return;
     }

   if (strcmp(szRequest, "END") == 0){
     digitalWrite(conLed, false);                    
     return;
  }
}

// Unknown command
void onUnknownCommand()
{
  messenger.sendCmd(kDebug,"UNKNOWN COMMAND"); 
}

// Request
void onRequest()
{
  char *szRequest = messenger.readStringArg();

  // INIT request 
  if (strcmp(szRequest, "INIT") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("SPAD");
    messenger.sendCmdArg(F("{97C072D7-7C96-4C70-BAD0-04C8CF56071A}"));
    messenger.sendCmdArg("Trim Wheel_FS20-1.0");
    messenger.sendCmdEnd();
    return;
  }

  // PING request
  if (strcmp(szRequest, "PING") == 0) {
    messenger.sendCmdStart(kRequest);
    messenger.sendCmdArg("PONG");
    messenger.sendCmdArg(messenger.readInt32Arg());
    messenger.sendCmdEnd();
    return;
  }

  // CONFIG request
  if (strcmp(szRequest, "CONFIG") == 0) {
    messenger.sendCmd(kRequest, "CONFIG");
    messenger.sendCmdEnd();
    return;
  }  
}

// Attach the command callbacks
void attachCommandCallbacks()
{
  messenger.attach(onUnknownCommand);
  messenger.attach(kRequest , onRequest);
  messenger.attach(kEvent, onEvent);  
}

// ------------------   E N C O D E R  C A L L B A C K -----------------------

void onEb1Encoder(EncoderButton& eb) {
  // Trim wheel UP
  if (eb.increment() == 1){
    messenger.sendCmd(kSimCommand,"SIMCONNECT:ELEV_TRIM_UP");
    messenger.sendCmdEnd();
  }
  // Trim wheel DOWN
  if (eb.increment() == -1){
    messenger.sendCmd(kSimCommand,"SIMCONNECT:ELEV_TRIM_DN");
    messenger.sendCmdEnd();
  }
}

// ------------------ M A I N  ----------------------

void setup()
{
  // Start the serial communication
  Serial.begin(115200);
  // Attach the callbacks to the Command Messenger
  attachCommandCallbacks();
  // Set up the connection led
  pinMode(conLed, OUTPUT); 
  digitalWrite(conLed, false); 
  // Set up the encoder
  eb1.setEncoderHandler(onEb1Encoder);
}

void loop()
{
  // Process incoming serial data, and perform callbacks
  messenger.feedinSerialData();
  // Update the encoder
  eb1.update();
}
