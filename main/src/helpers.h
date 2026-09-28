#ifndef HELPERS_H
#define HELPERS_H
#include <Arduino.h>

// apufunktiotioita
void interruptHelper(uint8_t pin);                              // asettaa keskeytykset oikeisiin osoitteisiin riippuen siitä mikä pinni on kyseessä
bool millisHelper(uint32_t time, uint16_t compareValue);        // millistimer, palauttaa true/false
float multiplierHelper(int percent, int potency);               // laskee kertoimen prosentista
int percentReductionHelper(uint16_t value, float multiplier);   // palauttaa value / kertoimella ---- esim. 15624 / 1.1 = 14203
int compareValuesHelper(int x, int y);                          // palauttaa 1(x > y), 0(x<y), -1(x == y) 
#endif