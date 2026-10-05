#include "src/buttons.h"
#include "src/display.h"
#include "src/leds.h"
#include "src/logic.h"
#include "src/timer.h"
#include "src/helpers.h"
#include "src/score.h"
#include "src/settings.h"

byte savedScores[ARR_LEN] = {0}; // tulostaulu

volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
int matchedCount;                        // kuinka monta lediä pelaaja on painanut oikein putkeen
byte sequence[20];                       // 20 ledin jälkeen ilman painallusta = häviö
int litCount;                            // kuinka monta lediä on yhteensä syttynyt
bool gameOn = false;
uint8_t timerPotency = 0; // katellaan jos tätä tarvii muualla ku timer.cpp
byte scorePointer = 0;

void setup()
{
  noInterrupts();

  // -- testing --
  Serial.begin(9600);
  Serial.println("Started");
  // -- testing --

  // clearEEPROM(); // kutsu tarvittaessa, tyhjentää muistin
  
  initializeDisplay();
  initializeLeds();
  initButtonsAndButtonInterrupts();
  
  readEEPROM();
  scoreHandler(scorePointer);
 
  Serial.println(savedScores[0]);

  interrupts();
}


// ---- TESTING -----
void jurgenPlayed(int sweet)
{
  if (gameOn)
  {
    buttonNumber = sweet;
  }
}
// ---- TESTING ----

// painallukset, Danielin
void buttonReader(int but)
{

}


void loop()
{

  buttonsHandler();

  if (buttonNumber > 0)
  {
      if (gameOn)
  {
    checkGame(buttonNumber);
  }
  else
  {
    switch (buttonNumber)
    {
    case 1:
      showResult(0);
      countDown(3);
      startTheGame();
      break;

    case 2:
      scorePointer++;
      if(scorePointer >= 255){
        scorePointer = 0;
      }
      scoreHandler(scorePointer);
      break;

    case 3:
      scorePointer--;
      if(scorePointer >= 255){
        scorePointer = 254;
      }
      scoreHandler(scorePointer);
      break;

    case 4:
      break;
    }
  }
    buttonNumber = -1;
  }

  // tän vois varmaa siirtää logic
  if (newTimerInterrupt == true)
  {
    byte pending = litCount - matchedCount; // monta painamatonta lediä on jonossa

    if (pending >= 20) // 20 painamatonta lediä = häviö
    {
      endGame();
    }
    else
    { 
      // Sammutetaan muut ledit
      clearAllLeds();
      logicControl();
      Serial.print("litcount: ");
      Serial.println(litCount);
      // tarkistetaan litcount
      isItTime();
      newTimerInterrupt = false;

      

      // ---- TESTING -----
      // jurgenPlayed(randomNumber);
      // ---- TESTING -----
    }
  }
}