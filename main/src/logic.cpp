#include "logic.h"
#include "Arduino.h"
#include "display.h"
#include "timer.h"
#include "leds.h"
#include "score.h"

void checkGame(byte nbrOfButtonPush) // tarkistaa mitä on painettu seuraavaa lediä vastaan. Oikein +1, väärin peli loppuu.
{
  byte expected = sequence[matchedCount % 20]; // sequence on 20 paikan ring buffer

  if (nbrOfButtonPush == expected && matchedCount < litCount) // painallus ennen ekaa lediä/kun niitä ei ole ja tuplapainallus = väärin
  {
    matchedCount++;
    showResult(matchedCount);
  }
  else
  {
    //-- test ---
    Serial.print("Expected: ");
    Serial.println(expected);
    Serial.print("pressed: ");
    Serial.println(nbrOfButtonPush);
    Serial.println("Score: ");
    Serial.println(matchedCount);
    // --- test ---

    endGame();
  }
}

void initializeGame() // nollaa pelin counterit ja flagit uutta peliä varten
{
  litCount = 0;
  matchedCount = 0;
  buttonNumber = -1;
  newTimerInterrupt = false;
  randomSeed(analogRead(A1));
  showResult(0);
}

void startTheGame()
{
  // valoshow pitää jotenki lopettaa joko täs tai sitte sielä ite valoshowssa
  // gameOn = true; // jos halutaan se näin ratkasta esimerkiks
  gameOn = true;
  initializeGame();
  initializeTimer();
}

void endGame()
{
  stopTimer();
  newTimerInterrupt = false;

  if (checkScore(matchedCount))
  {
    saveScore(matchedCount);
    writeEEPROM();
  }

  showResult(matchedCount);
  clearAllLeds();
  gameOn = false;
}