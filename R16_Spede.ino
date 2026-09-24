#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "logic.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
byte matchedCount;                       // kuinka monta lediä pelaaja on painanut oikein putkeen
volatile byte sequence[20];              // 20 ledin jälkeen ilman painallusta = häviö
volatile byte litCount;                  // kuinka monta lediä on yhteensä syttynyt
bool gameOn = false;
extern volatile uint8_t timerCounter;

void setup()
{
  Serial.begin(9600);
  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeDisplay();
}



void buttonGaming(int but){
    if (gameOn){
      checkGame(but);
      timerCounter++;
    }
    else{
      startTheGame(); 
      //painalluksen tunnistus tänne
    }
}




void loop()
{
  buttonsHandler();

  if (buttonNumber >= 0)
  {
    
    buttonGaming(buttonNumber);
    buttonNumber = -1;
  }

   
 if (newTimerInterrupt == true)
  {  
    // Sammutetaan muut ledit
    clearAllLeds();

    // Generoidaan satunnainen numero
    int randomNumber = random(1, 5);

    // Aktivoidaan satunnaista numeroa vastaava ledi
    setLed(randomNumber);
    
    // Käsitellään ajastin interrupti
    newTimerInterrupt = false;
  }
}
