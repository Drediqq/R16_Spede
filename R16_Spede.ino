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
  // -- testing --
  Serial.begin(9600);
  Serial.println("Started");
  // -- testing --

  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeDisplay();
}

void testCode(){
  if (buttonNumber > 0){
    Serial.print("Button press: ");
    Serial.println(buttonNumber);
  }
}

// painallukset, ehkä siirretään muualle?
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
  testCode();
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
    
    static byte oldNumber = 0; // tähän tallennetaan edellinen arvottu luku
    static byte randomNumber = 0; // arvottava luku

    // Generoidaan satunnainen numero
    while(randomNumber == oldNumber){
      randomNumber = random(1, 5);
    }
    oldNumber = randomNumber;
    

    // ---- TEST -----
    Serial.print("led number: ");
    Serial.println(randomNumber);
    // ---- TEST -----
    

    // Aktivoidaan satunnaista numeroa vastaava ledi
    setLed(randomNumber);
    
    // laitetaanpas sinne sequenceenkin se numero :D
    sequence[litCount] = randomNumber;
    
    // nostetaan myös litcounttia
    litCount++;
    
    // Käsitellään ajastin interrupti
    newTimerInterrupt = false;
  }
}
