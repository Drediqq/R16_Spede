#include "logic.h"
#include "SpedenSpelit.h"
#include "display.h"

void checkGame(byte nbrOfButtonPush) // tarkistaa mitä on painettu seuraavaa lediä vastaan. Oikein +1, väärin peli loppuu.
{
  if (!gameOn) // painallukset ei tee mitään kun peli eioo käynnissä
  {
    return;
  }

  byte expected = sequence[matchedCount % 20]; // sequence on 20 paikan ring buffer
  if (nbrOfButtonPush == expected && matchedCount < litCount)
  {
    matchedCount++;
    showResult(matchedCount);
  }
  else
  {
    TIMSK1 &= ~(1 << OCIE1A);
    showResult(matchedCount);
    gameOn = false;
  }
}

void initializeGame() // nollaa pelin counterit ja flagit uutta peliä varten
{
  litCount = 0;
  matchedCount = 0;
  buttonNumber = -1;
  newTimerInterrupt = false;
  randomSeed(analogRead(A1));
}

void startTheGame()
{
  // valoshow pitää jotenki lopettaa joko täs tai sitte sielä ite valoshowssa
  // gameOn = true; // jos halutaan se näin ratkasta esimerkiks
  gameOn = true;
  initializeGame();
  initializeTimer();
  TIMSK1 |= (1 << OCIE1A);
}