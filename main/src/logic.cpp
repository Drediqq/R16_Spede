#include "logic.h"
#include "timer.h"
#include "control.h"


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

void startTheGame() // aloittaa pelin
{ 
  gameOn = true;
  initializeGame();
  initializeTimer();
  newTimerInterrupt = true;
}

void endGame() // lopettaa pelin
{
  stopTimer();
  newTimerInterrupt = false;
  matchedCount = matchedCount * (difficulty * 0.5);

  if (checkScore(matchedCount))
  {
    saveScore(matchedCount);
    updateEEPROM();
  }

  showResult(matchedCount);
  clearAllLeds();
  show2(6);
  
  gameOn = false;
  standby();

}
