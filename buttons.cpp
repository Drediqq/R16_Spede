#include "buttons.h"
#include "Arduino.h"
#include <avr/io.h>


void buttonsHandler();
void buttonPress(uint8_t);

// Digitaali portin arvo
volatile uint8_t dState = 0xFF;
// edellisen painalluksen arvo
uint8_t lastPressedButton = 0xff;
// edellinen arvo joka ei debouncettanut
uint8_t stableState = 0xff;

// debounce ajastin ja delay jolla säädetään kuinka paljon aikaa välissä pitää olla vähintään
unsigned long debounceTimer = 0;
const unsigned long debounceDelay = 70; 


// asettaa keskeytykset oikeisiin osoitteisiin riippuen siitä mikä pinni on kyseessä
void interruptHelper(uint8_t pin){
  if(pin <= 7){
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << pin);
  }else if(pin <= 13){
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << pin);
  }else if(pin <= 19){
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << pin);
  }
}

void initButtonsAndButtonInterrupts(void){
  // alustaa pinnit ja niiden keskeytykset
  for(int i = firstPin; i <= lastPin; i++){
    pinMode(i, INPUT_PULLUP);
    interruptHelper(i);
  }
}

  // kaikki nappi keskeytykset kutsuu tätä ISRää ja tallennetaan dStateen miten napit on painettu
ISR(PCINT2_vect) {
   dState = PIND;
}  

// debouncettaa napit ja tarkistaa onko nappi ollut samassa arvossa tarpeeksi kauan ettei se ole bounce
void buttonsHandler() {
  //otetaan muuttujaan keskeytyksen kirjoittama arvo
  uint8_t pressedButton = dState;

  // jos lukema on muuttunut nollataan debounce ajastin
  if (pressedButton != lastPressedButton) {
    debounceTimer = millis();
    lastPressedButton = pressedButton;
  }
  // jos nappi ei ole hypännyt määritetyn ajan sisällä oletetaan että se on oikea painallus
  if ((millis() - debounceTimer) >= debounceDelay) {
    // tarkistetaan vielä että napin tila on vaihtunut 1 -> 0 tai 0 -> 1
    if(pressedButton != stableState){ 
      buttonPress(pressedButton);
    }
  }
}

// Selvittää mitä nappia painettiin ja asettaa sitten sen arvon buttonNumber muuttujaan (meidän tapauksessa 2, 3, 4 tai 5)
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
      buttonNumber = pin;
    }
  }
}