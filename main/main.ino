#include "src/buttons.h"
#include "src/display.h"
#include "src/leds.h"
#include "src/logic.h"
#include "src/timer.h"
#include "src/helpers.h"
#include "src/score.h"
#include "src/settings.h"
#include "src/control.h"

byte savedScores[ARR_LEN] = {0}; // tulostaulu

volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
int matchedCount;                        // kuinka monta lediä pelaaja on painanut oikein putkeen
byte sequence[20];                       // 20 ledin jälkeen ilman painallusta = häviö
int litCount;                            // kuinka monta lediä on yhteensä syttynyt
bool gameOn = false;
uint8_t timerPotency = 0; // katellaan jos tätä tarvii muualla ku timer.cpp




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
  
  standby();

  interrupts();
}




void loop(){
    
  buttonsHandler();
  if(!gameOn){
    if(!setDiff){
      show1();
    }
  }
  if (buttonNumber > 0){
    if(gameOn){
      checkGame(buttonNumber);
    }else{
      
      Serial.println(buttonNumber);
      buttonControl(buttonNumber);
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
      isItTime(litCount);
      newTimerInterrupt = false;

    
    }
  }
}