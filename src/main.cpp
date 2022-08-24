#include <Arduino.h>

#include <MIDIUSB.h>
#include "Controller.h"

//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 0;
//---How many potentiometers are connected directly to pins?--
byte NUMBER_POTS = 0;
//---How many buttons are connected to a multiplexer?---------
byte NUMBER_MUX_BUTTONS = 32;
//---How many potentiometers are connected to a multiplexer?--
byte NUMBER_MUX_POTS = 0;
//************************************************************

//***ANY MULTIPLEXERS? (74HC4067)************************************
// MUX address pins must be connected to Arduino UNO pins 2,3,4,5
// A0 = PIN2, A1 = PIN3, A2 = PIN4, A3 = PIN5
//*******************************************************************
// Mux NAME (OUTPUT PIN, , How Many Mux Pins?(8 or 16) , Is It Analog?);

Mux M1(8, 16, false);  // Digital multiplexer on Arduino pin 10
Mux M2(9, 16, false); // Digital multiplexer on Arduino pin 10
// Mux M3(11, 16, false); // Digital multiplexer on Arduino pin 10
// Mux M2(A5, 8, true); //Analog multiplexer on Arduino analog pin A0
//*******************************************************************

//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
// Pot (Pin Number, Command, CC Control, Channel Number)
//**Command parameter is for future use**

// Pot PO1(18, 0, 1, 2);
// Pot PO2(19, 0, 10, 1);
// Pot PO3(20, 0, 22, 1);
// Pot PO4(21, 0, 118, 1);
// Pot PO5(A4, 0, 30, 1);
// Pot PO6(A5, 0, 31, 1);
//*******************************************************************
// Add pots used to array below like this->  Pot *POTS[] {&PO1, &PO2, &PO3, &PO4, &PO5, &PO6};
Pot *POTS[]{};
//*******************************************************************

//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
// Button (Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

// Button BU1(2, 0, 60, 1, 5);
// Button BU2(3, 0, 61, 1, 5);
// Button BU3(4, 0, 62, 1, 5);
// Button BU4(5, 0, 63, 1, 5);
// Button BU5(6, 0, 64, 1, 5);
// Button BU6(7, 0, 65, 1, 5);
// Button BU7(8, 0, 66, 1, 5);
// Button BU8(9, 0, 67, 1, 5);
// Button BU9(10, 0, 68, 1, 5);
// Button BU10(14, 0, 69, 1, 5);
// Button BU11(15, 0, 70, 1, 5);
// Button BU12(16, 0, 71, 1, 5);
//*******************************************************************
// Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8, &BU9, &BU10, &BU11, &BU12};
Button *BUTTONS[]{};
// //*******************************************************************

// //***DEFINE BUTTONS CONNECTED TO MULTIPLEXER*************************
// // Button::Button(Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce)
// //** Command parameter 0=NOTE  1=CC  2=Toggle CC **

Button MBU1a(M1, 0, 0, 70, 1, 5);
Button MBU2a(M1, 1, 0, 71, 1, 5);
Button MBU3a(M1, 2, 0, 72, 1, 5);
Button MBU4a(M1, 3, 0, 73, 1, 5);
Button MBU5a(M1, 4, 0, 74, 1, 5);
Button MBU6a(M1, 5, 0, 75, 1, 5);
Button MBU7a(M1, 6, 0, 76, 1, 5);
Button MBU8a(M1, 7, 0, 77, 1, 5);
Button MBU9a(M1, 8, 0, 78, 1, 5);
Button MBU10a(M1, 9, 0, 79, 1, 5);
Button MBU11a(M1, 10, 0, 80, 1, 5);
Button MBU12a(M1, 11, 0, 81, 1, 5);
Button MBU13a(M1, 12, 0, 82, 1, 5);
Button MBU14a(M1, 13, 0, 83, 1, 5);
Button MBU15a(M1, 14, 0, 84, 1, 5);
Button MBU16a(M1, 15, 0, 85, 1, 5);

Button MBU1b(M2, 0, 0, 70, 2, 5);
Button MBU2b(M2, 1, 0, 71, 2, 5);
Button MBU3b(M2, 2, 0, 72, 2, 5);
Button MBU4b(M2, 3, 0, 73, 2, 5);
Button MBU5b(M2, 4, 0, 74, 2, 5);
Button MBU6b(M2, 5, 0, 75, 2, 5);
Button MBU7b(M2, 6, 0, 76, 2, 5);
Button MBU8b(M2, 7, 0, 77, 2, 5);
Button MBU9b(M2, 8, 0, 78, 2, 5);
Button MBU10b(M2, 9, 0, 79, 2, 5);
Button MBU11b(M2, 10, 0, 80, 2, 5);
Button MBU12b(M2, 11, 0, 81, 2, 5);
Button MBU13b(M2, 12, 0, 82, 2, 5);
Button MBU14b(M2, 13, 0, 83, 2, 5);
Button MBU15b(M2, 14, 0, 84, 2, 5);
Button MBU16b(M2, 15, 0, 85, 2, 5);

// Button MBU1c(M3, 0, 0, 70, 3, 5);
// Button MBU2c(M3, 1, 0, 71, 3, 5);
// Button MBU3c(M3, 2, 0, 72, 3, 5);
// Button MBU4c(M3, 3, 0, 73, 3, 5);
// Button MBU5c(M3, 4, 0, 74, 3, 5);
// Button MBU6c(M3, 5, 0, 75, 3, 5);
// Button MBU7c(M3, 6, 0, 76, 3, 5);
// Button MBU8c(M3, 7, 0, 77, 3, 5);
// Button MBU9c(M3, 8, 0, 78, 3, 5);
// Button MBU10c(M3, 9, 0, 79, 3, 5);
// Button MBU11c(M3, 10, 0, 80, 3, 5);
// Button MBU12c(M3, 11, 0, 81, 3, 5);
// Button MBU13c(M3, 12, 0, 82, 3, 5);
// Button MBU14c(M3, 13, 0, 83, 3, 5);
// Button MBU15c(M3, 14, 0, 84, 3, 5);
// Button MBU16c(M3, 15, 0, 85, 3, 5);
// //*******************************************************************
////Add multiplexed buttons used to array below like this->  Button *MUXBUTTONS[] {&MBU1, &MBU2, &MBU3, &MBU4, &MBU5, &MBU6.....};
Button *MUXBUTTONS[]{
    &MBU1a, &MBU2a, &MBU3a, &MBU4a, &MBU5a, &MBU6a, &MBU7a, &MBU8a,
    &MBU9a, &MBU10a, &MBU11a, &MBU12a, &MBU13a, &MBU14a, &MBU15a, &MBU16a,
    &MBU1b, &MBU2b, &MBU3b, &MBU4b, &MBU5b, &MBU6b, &MBU7b, &MBU8b,
    &MBU9b, &MBU10b, &MBU11b, &MBU12b, &MBU13b, &MBU14b, &MBU15b, &MBU16b
    // &MBU1c, &MBU2c, &MBU3c, &MBU4c, &MBU5c, &MBU6c, &MBU7c, &MBU8c,
    // &MBU9c, &MBU10c, &MBU11c, &MBU12c, &MBU13c, &MBU14c, &MBU15c, &MBU16c
};

//*******************************************************************

//***DEFINE POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
// Pot::Pot(Mux mux, byte muxpin, byte command, byte control, byte channel)
//**Command parameter is for future use**

// Pot MPO1(M2, 0, 0, 1, 1);
// Pot MPO2(M2, 1, 0, 7, 1);
// Pot MPO3(M2, 2, 0, 50, 1);
// Pot MPO4(M2, 3, 0, 55, 2);
// Pot MPO5(M2, 4, 0, 50, 1);
// Pot MPO6(M2, 5, 0, 55, 2);
// Pot MPO7(M2, 6, 0, 50, 1);
// Pot MPO8(M2, 7, 0, 55, 2);
// Pot MPO9(M2, 8, 0, 50, 1);
// Pot MPO10(M2, 9, 0, 55, 2);
// Pot MPO11(M2, 10, 0, 50, 1);
// Pot MPO12(M2, 11, 0, 55, 2);
// Pot MPO13(M2, 12, 0, 50, 1);
// Pot MPO14(M2, 13, 0, 55, 2);
// Pot MPO15(M2, 14, 0, 50, 1);
// Pot MPO16(M2, 15, 0, 55, 2);
//*******************************************************************
// Add multiplexed pots used to array below like this->  Pot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
Pot *MUXPOTS[]{};
//*******************************************************************
void noteOn(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


void setup()
{
  // MIDI.begin(MIDI_CHANNEL_OFF);
}

void controlChange(byte channel, byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

//*****************************************************************
void updateButtons()
{

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1)
  {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0)
    {
      switch (BUTTONS[i]->Bcommand)
      {
      case 0: // Note
        noteOn(BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue, 127);
        MidiUSB.flush();
        break;
      case 1: // CC
        controlChange(BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue, 127);
        MidiUSB.flush();
        break;
      case 2: // Toggle
        if (BUTTONS[i]->Btoggle == 0)
        {
          controlChange(BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue, 127);
          BUTTONS[i]->Btoggle = 1;
          MidiUSB.flush();
        }
        else if (BUTTONS[i]->Btoggle == 1)
        {
          controlChange(BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue, 0);
          BUTTONS[i]->Btoggle = 0;
          MidiUSB.flush();
        }
        break;
      }
    }

    //  Button is not pressed
    if (message == 1)
    {
      switch (BUTTONS[i]->Bcommand)
      {
      case 0:
        noteOff(BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue, 0);
        MidiUSB.flush();
        break;
      case 1:
        controlChange(BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue, 0);
        MidiUSB.flush();
        break;
      }
    }
  }
}
//*******************************************************************
void updateMuxButtons()
{

  // Cycle through Mux Button array
  for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1)
  {

    MUXBUTTONS[i]->muxUpdate();
    byte message = MUXBUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0)
    {
      switch (MUXBUTTONS[i]->Bcommand)
      {
      case 0: // Note
        noteOn(MUXBUTTONS[i]->Bchannel, MUXBUTTONS[i]->Bvalue, 127);
        MidiUSB.flush();
        break;
      case 1: // CC
        controlChange(MUXBUTTONS[i]->Bchannel, MUXBUTTONS[i]->Bvalue, 127);
        MidiUSB.flush();
        break;
      case 2: // Toggle
        if (MUXBUTTONS[i]->Btoggle == 0)
        {
          controlChange(MUXBUTTONS[i]->Bchannel, MUXBUTTONS[i]->Bvalue, 127);
          MidiUSB.flush();
          //  (channel, CC number,  CC value) // channel, note, velocity
          MUXBUTTONS[i]->Btoggle = 1;
        }
        else if (MUXBUTTONS[i]->Btoggle == 1)
        {
          controlChange(MUXBUTTONS[i]->Bchannel, MUXBUTTONS[i]->Bvalue, 0);
          MidiUSB.flush();
          MUXBUTTONS[i]->Btoggle = 0;
        }
        break;
      }
    }
    //  Button is not pressed
    if (message == 1)
    {
      switch (MUXBUTTONS[i]->Bcommand)
      {
      case 0:
        noteOff(MUXBUTTONS[i]->Bchannel, MUXBUTTONS[i]->Bvalue, 0);
        MidiUSB.flush();
        break;
      case 1:

        controlChange(MUXBUTTONS[i]->Bchannel, MUXBUTTONS[i]->Bvalue, 0); // channel control value
        MidiUSB.flush();
        break;
      }
    }
  }
}
//***********************************************************************
void updatePots()
{
  for (int i = 0; i < NUMBER_POTS; i = i + 1)
  {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255)
      controlChange(POTS[i]->Pchannel, POTS[i]->Pcontrol, potmessage);
    MidiUSB.flush();
  }
}
//***********************************************************************
void updateMuxPots()
{
  for (int i = 0; i < NUMBER_MUX_POTS; i = i + 1)
  {
    MUXPOTS[i]->muxUpdate();
    byte potmessage = MUXPOTS[i]->getValue();
    if (potmessage != 255)
      controlChange(MUXPOTS[i]->Pchannel, MUXPOTS[i]->Pcontrol, potmessage);
    MidiUSB.flush();
  }
}

void loop()
{

  if (NUMBER_BUTTONS != 0)
    updateButtons();
  if (NUMBER_POTS != 0)
    updatePots();
  if (NUMBER_MUX_BUTTONS != 0)
    updateMuxButtons();
  if (NUMBER_MUX_POTS != 0)
    updateMuxPots();
}



