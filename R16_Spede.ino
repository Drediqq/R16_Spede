#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
byte matchedCount;                       // kuinka monta lediä pelaaja on painanut oikein putkeen
volatile byte sequence[20];              // 20 ledin jälkeen ilman painallusta = häviö
volatile byte litCount;                  // kuinka monta lediä on yhteensä syttynyt

void setup()
{
  /*
    Initialize here all modules
  */
}

void loop()
{
  if (buttonNumber >= 0)
  {
    // start the game if buttonNumber == 4
    // check the game if 0<=buttonNumber<4
  }

  if (newTimerInterrupt == true)
  {
    // new random number must be generated
    // and corresponding let must be activated
  }
}

void initializeTimer(void)
{
  // see requirements for the function from SpedenSpelit.h
}
ISR(TIMER1_COMPA_vect)
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
}

void checkGame(byte nbrOfButtonPush)
{
  // see requirements for the function from SpedenSpelit.h
}

void initializeGame()
{
  litCount = 0;
  matchedCount = 0;
  buttonNumber = -1;
  newTimerInterrupt = false;
  randomSeed(analogRead(A1));
}

void startTheGame()
{
  // see requirements for the function from SpedenSpelit.h
}
