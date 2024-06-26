#include <Wire.h>
#include <Zumo32U4.h>
#include "RemoteConstants.h"
#include "RemoteDecoder.h"
#include <Zumo32u4IRsender.h>

#define DEVICE_ID 7
Zumo32U4IRsender ZumoIrSenderRight(DEVICE_ID, RIGHT_IR);
Zumo32U4IRsender ZumoIrSenderLeft(DEVICE_ID, LEFT_IR);

// This variable sets the amount of time (in milliseconds) that
// we wait before considering the current message from the remote
// to have expired.  This type of remote typically sends a repeat
// command every 109 ms, so a timeout value of 115 was chosen.
// You can increase this timeout to 230 if you want to be more
// tolerant of errors that occur while you are holding down the
// button, but it will make the robot slower to respond when you
// release the button.
const uint16_t messageTimeoutMs = 115;

// This variable is true if the last message received from the
// remote is still active, meaning that we are still performing
// the action specified by the message.  A message will be active
// if the remote button is being held down and the robot has been
// successfully receiving messages from the remote since the
// button was pressed.
bool messageActive = false;

// This is the time that the current message from the remote was
// last verified, in milliseconds.  It is used to implement the
// timeout defined above.
uint16_t lastMessageTimeMs = 0;

// Change next line to this if you are using the older Zumo 32U4
// with a black and green LCD display:
// Zumo32U4LCD display;
Zumo32U4LCD display;

Zumo32U4Motors motors;
Zumo32U4Buzzer buzzer;
Zumo32U4ButtonA buttonA;

RemoteDecoder decoder;

void setup()
{
  decoder.init();

  display.clear();
  display.print(F("Waiting"));
}

int CommandCount=0;
unsigned long RelayDelay=100;
unsigned long RelayTime=0;
void loop()
{
  decoder.service();

  // Turn on the yellow LED if a message is active.
  ledYellow(messageActive);

  // Turn on the red LED if we are in the middle of receiving a
  // new message from the remote.  You should see the red LED
  // blinking about 9 times per second while you hold a remote
  // button down.
  ledRed(decoder.criticalTime());

  if (decoder.criticalTime())
  {
    // We are in the middle of receiving a message from the
    // remote, so we should avoid doing anything that might take
    // more than a few tens of microseconds, and call
    // decoder.service() as often as possible.
  }
  else
  {
    // We are not in a critical time, so we can do other things
    // as long as they do not take longer than about 7.3 ms.
    // Delays longer than that can cause some remote control
    // messages to be missed.

    processRemoteEvents();
  }

  // Check how long ago the current message was last verified.
  // If it is longer than the timeout time, then the message has
  // expired and we should stop executing it.
  if (messageActive && (uint16_t)(millis() - lastMessageTimeMs) > messageTimeoutMs)
  {
    messageActive = false;
    stopCurrentCommand();
  }
}

void processRemoteEvents()
{
  if (decoder.getAndResetMessageFlag())
  {
    // The remote decoder received a new message, so record what
    // time it was received and process it.
    lastMessageTimeMs = millis();
    messageActive = true;
    processRemoteMessage(decoder.getMessage());
  }

  if (decoder.getAndResetRepeatFlag())
  {
    // The remote decoder receiver a "repeat" command, which is
    // sent about every 109 ms while the button is being held
    // down.  It contains no data.  We record what time the
    // repeat command was received so we can know that the
    // current message is still active.
    lastMessageTimeMs = millis();
  }
}

void processRemoteMessage(const uint8_t * message)
{
  // Print the raw message on the first line of the display, in hex.
  // The first two bytes are usually an address, and the third
  // byte is usually a command.  The last byte is supposed to be
  // the bitwise inverse of the third byte, and if that is the
  // case, then we don't print it.
  display.clear();
  char buffer[9];
  if (message[2] + message[3] == 0xFF)
  {
    sprintf(buffer, "%02X%02X %02X ",
      message[0], message[1], message[2]);
  }
  else
  {
    sprintf(buffer, "%02X%02X%02X%02X",
      message[0], message[1], message[2], message[3]);
  }
  display.print(buffer);

  // Go to the next line of the display.
  display.gotoXY(0, 1);

  // Make sure the address matches what we expect.
  if (message[0] != remoteAddressByte0 ||
    message[1] != remoteAddressByte1)
  {
    display.print(F("bad addr"));
    return;
  }

  // Make sure that the last byte is the logical inverse of the
  // command byte.
  if (message[2] + message[3] != 0xFF)
  {
    display.print(F("bad cmd"));
    return;
  }

  stopCurrentCommand();
  processRemoteCommand(message[2]);
}


// Start running the new command.
void processRemoteCommand(uint8_t command)
{
  if (CommandCount==1){
    motors.setSpeeds(50,-50);
  }
  switch(command)
  {
  case remoteUp:
    display.print(F("COME HERE"));
    
    break;

  case remoteDown:
    display.print(F("down"));
    motors.setSpeeds(-400, -400);
    break;

  case remoteLeft:
    display.print(F("left"));
    motors.setSpeeds(-250, 250);
    break;

  case remoteRight:
    display.print(F("right"));
    motors.setSpeeds(250, -250);
    break;

  case remoteStopMode:
    display.print(F("stop"));
    break;

  case remoteEnterSave:
    display.print(F("CHARGE NOW"));
    CommandCount=1;
    motors.setSpeeds(50,50);
    break;

  case remoteVolMinus:
    display.print(F("vol-"));
    break;

  case remoteVolPlus:
    display.print(F("vol+"));
    break;

  case remotePlayPause:
    display.print(F("play"));
    break;

  case remoteSetup:
    display.print(F("setup"));
    break;

  case remoteBack:
    display.print(F("back"));
    break;

  case remote0:
    display.print(F("0"));
    break;

  case remote1:
    display.print(F("1"));
    buzzer.playNote(NOTE_C(4), 200, 15);
    break;

  case remote2:
    display.print(F("2"));
    buzzer.playNote(NOTE_D(4), 200, 15);
    break;

  case remote3:
    display.print(F("3"));
    buzzer.playNote(NOTE_E(4), 200, 15);
    break;

  case remote4:
    display.print(F("4"));
    break;

  case remote5:
    display.print(F("5"));
    break;

  case remote6:
    display.print(F("6"));
    break;

  case remote7:
    display.print(F("7"));
    break;

  case remote8:
    display.print(F("8"));
    break;

  case remote9:
    display.print(F("9"));
    break;
  }
}

// Stops the current remote control command.  This is called when
// a new command is received or if the current command has
// expired.
void stopCurrentCommand()
{
  motors.setSpeeds(0, 0);
  buzzer.stopPlaying();
}