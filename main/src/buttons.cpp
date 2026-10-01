#include "buttons.h"
#include "helpers.h"
#include "settings.h"


volatile uint8_t dState = 0xFF; // Digitaali portin arvo
uint8_t lastPressedButton = 0xff; // edellisen painalluksen arvo
uint8_t stableState = 0xff; // edellinen arvo joka ei debouncettanut


// alustaa pinnit ja niiden keskeytykset
void initButtonsAndButtonInterrupts(void){
  for(int i = firstPin; i <= lastPin; i++){
    pinMode(i, INPUT_PULLUP);
    interruptHelper(i);
  }
}

// kaikki nappi keskeytykset kutsuu tätä ISRää ja tallennetaan dStateen miten napit on painettu
ISR(PCINT2_vect) {
// PIND
// [PIND7] [PIND6] [PIND5] [PIND4] [PIND3] [PIND2]  [PIND1]  [PIND0]    | PIND
// ---------------------------------------------------------------------|----------------
// [ x ]   [ x ]   [ 1 ]   [ 1 ]   [ 1 ]   [ 1 ]    [ x ]    [ x ]      | 0bxx1111xx  
//                   |       |       |       |                          |                  
//               (näiden pinnien tilasta välitetään)                                  
// --------------------------------------------------------------------------------------
   dState = PIND;
}


// debouncettaa napit ja tarkistaa onko nappi ollut samassa arvossa tarpeeksi kauan ettei se ole bounce
void buttonsHandler() {
  static unsigned long debounceTimer = 0;
  uint8_t pressedButton = dState; //otetaan muuttujaan keskeytyksen kirjoittama arvo

  // jos lukema on muuttunut nollataan debounce ajastin
  if (pressedButton != lastPressedButton) {
    debounceTimer = millis();
    lastPressedButton = pressedButton;
  }
  // jos nappi ei ole hypännyt määritetyn ajan sisällä oletetaan että se on oikea painallus
  if (millisHelper(debounceTimer, DEBOUNCE_DELAY)) {
    // tarkistetaan vielä että napin tila on vaihtunut 1 -> 0 tai 0 -> 1
    if(pressedButton != stableState){ 
      buttonPress(pressedButton);
    }
  }
}

// Selvittää mitä nappia painettiin ja asettaa sitten sen arvon buttonNumber muuttujaan
void buttonPress(uint8_t button) {
  // selvitetään mikä bitti muuttui XORilla
  uint8_t omegaButton = button ^ stableState;

  // asetetaan stableState esim vaikka 1101 tai 1011 tai 0111 tai 1110
  stableState = button;
  
  // jos mikään bitti ei muuttunut, lopetaan tähän
  if(omegaButton == 0){
    return;
  }

  // tarkistetaan onko joku pinni mennyt 1 -> 0
  for (uint8_t pin = firstPin; pin <= lastPin; pin++) {
    if ((omegaButton & (1 << pin)) && !(button & (1 << pin))) {
      buttonNumber = pin-1;
    }
  }
}
