#ifndef HELPERS_H
#define HELPERS_H
#include <Arduino.h>

// Yleishyödylliset apufunktiot

bool millisHelper(uint32_t time, uint16_t compareValue);    // millistimer, palauttaa true/false
float getMultiplier(int percent, int potency);              // laskee kertoimen prosentista
bool isValueOverN(int xValue, int yValue);                  // palauttaa true, jos x on suurempi kuin y
int decreaseByPercent(uint16_t value, float multiplier);    // palauttaa value / kertoimella ---- esim. 15624 / 1.1 = 14203

#endif