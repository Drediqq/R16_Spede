#include "control.h"

byte difficulty = 1; // vaikeustaso
bool setDiff = false; //vaikeustaso asetin päällä/pois
byte scorePointer = 0; // highscore osoitin

// palauttaa alkutilan
void standby(){
  setDiff = false;
  difficulty = 1;
  clearAllLeds();
  scorePointer = 0;
  scoreHandler(scorePointer);
}

// arpoo numerot ja sytyttelee ledit
void logicControl(){
      static byte oldNumber = 0;    // tähän tallennetaan edellinen arvottu luku
      static byte randomNumber = 0; // arvottava luku

      // Arvotaan satunnainen numero
      while (randomNumber == oldNumber)
      {
        randomNumber = random(1, 5);
      }
      oldNumber = randomNumber;

      // Aktivoidaan satunnaista numeroa vastaava ledi
      setLed(randomNumber);

      // laitetaan arvottu luku sequenceen
      sequence[litCount % 20] = randomNumber;

      // nostetaan myös litcounttia
      litCount++;
}

// nappiohjaus
void buttonControl(int but){
  // näppäimet 1,2,3,4 vasemmalta oikealle.  
  switch (but)
    {
    //pelin aloitusnäppäin 
    case 1:
      if(!setDiff){ 
        clearAllLeds();
        setDiff = !setDiff;
        showResult(difficulty);
        setLed(difficulty);
      
      // peli käynnistyy toisella painalluksella.
      }else{ 
        setDiff = !setDiff;
        clearAllLeds();
        showResult(0);
        countDown(3);
        startTheGame();
      }
      break;
    // scoren selausnäppäin 2
    case 2:
      if(!setDiff){
        if(!setDiff){
          scorePointer--;
          if(scorePointer >= 255){
            scorePointer = 254;
          }
          scoreHandler(scorePointer);
        }
    }
      break;
    // scoren selausnäppäin 3
    case 3:
      if(!setDiff){
        if(!setDiff){
          scorePointer++;
          if(scorePointer >= 255){ // skipataan 255
            scorePointer = 0;
          }
          scoreHandler(scorePointer);
        }
      }
      break;
    // vaikeustaso asetin 4
    case 4:
      if(setDiff){
        difficulty++; // nostetaan vaikeustasoa joka painalluksella
        if(difficulty > 4){
          difficulty = 1; // palataan takaisin vaikeustaso 1 kun mennään yli 4
          clearAllLeds();
        }
        setLed(difficulty);
        showResult(difficulty);
      }
      break;
    }
}