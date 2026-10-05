#include "helpers.h"

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

// vertaa millis() annettuun aikaan, palauttaa true/false
bool millisHelper(uint32_t time, uint16_t compareValue){
  return (millis() - time) >= compareValue; //palauttaa true/false
}

// laskee kertoimen prosentista
float multiplierHelper(int percent, int potency){
  float base = 1 + (percent * 0.01);  // 1 + (stepSize * 0.01),  esim. 1 + 10(%) * 0.01 = 1.1
  return pow(base, potency);       // base^step,              esim. 1.1² (²=step)
}

// palauttaa value / divider esim. 15624 / 1.1 = 14203
int percentReductionHelper(uint16_t value, float divider) {
  return value / divider;
}

// palauttaa: 
//  1 = x suurempi 
//  -1 = x pienempi 
//  0 x,y yhtäsuuret
int compareValuesHelper(int xValue, int yValue){ 
  if (xValue > yValue)  return 1;   // X on suuremp
  if (xValue < yValue)  return -1;  // X on pienempi
  return 0; // yhtäsuuret
}