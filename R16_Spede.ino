#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "logic.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
byte matchedCount;                       // kuinka monta lediä pelaaja on painanut oikein putkeen
volatile byte sequence[20];              // 20 ledin jälkeen ilman painallusta = häviö
volatile byte litCount;                  // kuinka monta lediä on yhteensä syttynyt
bool gameOn = false;

void setup()
{
  Serial.begin(9600);
  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeDisplay();
}

void loop()
{
  buttonsHandler();

  if (buttonNumber >= 0)
  {
    if (buttonNumber == 1)
    {
      writeByte(1, 1);
      setLed(1);
    }
    if (buttonNumber == 2)
    {
      writeByte(2, 1);
      setLed(2);
    }
    if (buttonNumber == 3)
    {
      writeByte(3, 1);
      setLed(3);
    }
    if (buttonNumber == 4 && newTimerInterrupt == false)
    {
      writeByte(4, 1);
      setLed(4);
      // startTheGame();
    }
    // start the game if buttonNumber == 4
    // check the game if 0<=buttonNumber<4
    buttonNumber = -1;
  }

  if (newTimerInterrupt == true)
  {
    // new random number must be generated
    // and corresponding let must be activated
  }
}
