#include "logic.h"


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
  newTimerInterrupt = true;
}

void endGame()
{
  stopTimer();
  newTimerInterrupt = false;

  if (checkScore(matchedCount))
  {
    saveScore(matchedCount);
    updateEEPROM();
  }

  showResult(matchedCount);
  clearAllLeds();
  gameOn = false;
}
void logicControl(){
      static byte oldNumber = 0;    // tähän tallennetaan edellinen arvottu luku
      static byte randomNumber = 0; // arvottava luku

      // Generoidaan satunnainen numero
      while (randomNumber == oldNumber)
      {
        randomNumber = random(1, 5); // pitäsköhän arpoa jossain pelin alotuksessa paljo numeroita
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
}