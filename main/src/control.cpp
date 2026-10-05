#include "control.h"

#include "leds.h"
#include "display.h"
#include "logic.h"

extern byte sequence[];
extern int litCount;

byte difficulty = 1;
bool setDiff = false;
byte scorePointer = 0;

void standby(){
  setDiff = false;
  difficulty = 1;
  clearAllLeds();
  scorePointer = 0;
  scoreHandler(scorePointer);

}

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

void buttonControl(int but){
    switch (but)
    {
    case 1:
      if(!setDiff){
        clearAllLeds();
        setDiff = !setDiff;
        showResult(difficulty);
        setLed(difficulty);
      }else{
        setDiff = !setDiff;
        clearAllLeds();
        showResult(0);
        countDown(3);
        startTheGame();
      }
      break;

    case 2:
    if(!setDiff){
      scorePointer++;
      if(scorePointer >= 255){
        scorePointer = 0;
      }
      scoreHandler(scorePointer);
    }
      break;

    case 3:
      if(!setDiff){
      scorePointer--;
      if(scorePointer >= 255){
        scorePointer = 254;
      }
      scoreHandler(scorePointer);
    }
      break;

    case 4:
      if(setDiff){
        difficulty++;
        
        
        if(difficulty > 4){
          difficulty = 1;
          clearAllLeds();
        }
        setLed(difficulty);
        showResult(difficulty);
      }
      
      break;
    }
}