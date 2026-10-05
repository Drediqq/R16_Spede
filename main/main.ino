#include "src/buttons.h"
#include "src/control.h"
#include "src/display.h"
#include "src/helpers.h"
#include "src/leds.h"
#include "src/logic.h"
#include "src/score.h"
#include "src/settings.h"
#include "src/timer.h"

byte savedScores[ARR_LEN] = {0}; // tulostaulu

volatile int buttonNumber = -1;          // for buttons interrupt handler
volatile bool newTimerInterrupt = false; // for timer interrupt handler
int matchedCount;  // kuinka monta lediä pelaaja on painanut oikein putkeen
byte sequence[20]; // 20 ledin jälkeen ilman painallusta = häviö
int litCount;      // kuinka monta lediä on yhteensä syttynyt
bool gameOn = false;
uint8_t timerPotency = 0; // katellaan jos tätä tarvii muualla ku timer.cpp

void setup() {
  noInterrupts();

  // clearEEPROM(); // kutsu tarvittaessa, tyhjentää muistin

  // display/leds/buttons init
  initializeDisplay();
  initializeLeds();
  initButtonsAndButtonInterrupts();
  
  // EEPROM init
  writeEEPROM();
  delay(10);
  readEEPROM();

  //Standby
  standby();

  interrupts();
}

void loop() {
  buttonsHandler(); // asettaa painetun napin arvon buttonNumber muuttujaan

  // jos peli eikä vaikeustasovalitsin ole päällä, pyöritellään valoshowta
  if (!gameOn) {
    if (!setDiff) {
      show1();
    }
  }

  // nappien ohjaus
  if (buttonNumber > 0) {
    if (gameOn) {
      checkGame(buttonNumber);
    } else {
      buttonControl(buttonNumber);
    }
    buttonNumber = -1;
  }
  
  // ledien ohjaus pelatessa
  if (newTimerInterrupt == true) {
    byte pending = litCount - matchedCount; // montako painamatonta lediä on jonossa

    if (pending >= 20) // 20 painamatonta lediä = häviö
    {
      endGame(); // peli päättyy
    } else {
      clearAllLeds(); // Sammutetaan ledit
      logicControl(); // sytyttää ledin
      isItTime(litCount); // tarkistetaan onko sytytetty tarpeeksi
      newTimerInterrupt = false;
    }
  }
}