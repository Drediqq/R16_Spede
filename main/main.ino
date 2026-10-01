#include "src/buttons.h"
#include "src/display.h"
#include "src/leds.h"
#include "src/logic.h"
#include "src/timer.h"
#include "src/helpers.h"
#include "src/score.h"
#include "src/settings.h"


// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
byte savedScores[ARR_LEN] = {0};          // tulostaulu
volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
byte matchedCount;                       // kuinka monta lediä pelaaja on painanut oikein putkeen
volatile byte sequence[20];              // 20 ledin jälkeen ilman painallusta = häviö
volatile int litCount;                  // kuinka monta lediä on yhteensä syttynyt
bool gameOn = false;
volatile uint8_t timerCounter = 0;
volatile uint8_t timerPotency = 0; // katellaan jos tätä tarvii muualla ku timer.cpp
byte scorePointer = 0;

void setup()
{
  // -- testing --
  Serial.begin(9600);
  Serial.println("Started");
  // -- testing --
  //clearEEPROM(); // kutsu tarvittaessa, tyhjentää muistin
  readEEPROM();
  scoreHandler(scorePointer);
  initializeDisplay();
  initializeLeds();
  initButtonsAndButtonInterrupts();
  
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

// painallukset, ehkä siirretään muualle?
void buttonGaming(int but)
{
  if (gameOn)
  {
    checkGame(but);
  }
  else
  {
    switch (but)
    {
    case 1:
      showResult(0);
      countDown(3);
      startTheGame();
      break;

    case 2:
    scoreHandler(scorePointer++);
      break;

    case 3:
    scoreHandler(scorePointer--);
      break;

    case 4:
      break;
    }
  }
}

void loop()
{
  buttonsHandler();
  
  if (buttonNumber > 0)
  {
    buttonGaming(buttonNumber);
    buttonNumber = -1;
  }

  if (newTimerInterrupt == true)
  {
    newTimerInterrupt = false;              // nollataan heti
    byte pending = litCount - matchedCount; // monta painamatonta lediä on jonossa

    if (pending >= 20) // 20 painamatonta lediä = häviö
    {
      endGame();
    }
    else
    {
      // Sammutetaan muut ledit
      clearAllLeds();

      static byte oldNumber = 0;    // tähän tallennetaan edellinen arvottu luku
      static byte randomNumber = 0; // arvottava luku

      // Generoidaan satunnainen numero
      while (randomNumber == oldNumber)
      {
        randomNumber = random(1, 5);
      }
      oldNumber = randomNumber;

      // ---- TEST -----
      Serial.print("led number: ");
      Serial.println(randomNumber);
      // ---- TEST -----

      // Aktivoidaan satunnaista numeroa vastaava ledi
      setLed(randomNumber);

      // laitetaan arvottu luku sequenceen
      sequence[litCount % 20] = randomNumber;

      // nostetaan myös litcounttia
      litCount++;
      // tarkistetaan litcount
      isItTime();

      // ---- TESTING -----
      //jurgenPlayed(randomNumber);
      // ---- TESTING -----
    }
  }
}