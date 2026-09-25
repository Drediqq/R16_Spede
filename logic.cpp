#include "logic.h"
#include "Arduino.h"
#include "SpedenSpelit.h"
#include "display.h"
#include "timer.h"
#include "leds.h"

void checkGame(byte nbrOfButtonPush) // tarkistaa mitä on painettu seuraavaa lediä vastaan. Oikein +1, väärin peli loppuu.
{
  // -- tätä ei pitäis tarvita
  if (!gameOn) // painallukset ei tee mitään kun peli eioo käynnissä
  {
    return;
  }
  // --

  byte expected = sequence[matchedCount % 20]; // sequence on 20 paikan ring buffer
 
  
  if (nbrOfButtonPush == expected) //  && matchedCount < litCount ei pitäs olla tarpeellinen
  {
    matchedCount++;
    Serial.println(matchedCount);
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
    
    stopTimer();
    showResult(matchedCount);
    clearAllLeds();
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
  
}