#include "helpers.h"
// millistimer, palauttaa true/false
bool millisHelper(uint32_t time, uint16_t compareValue){
  return (millis() - time) >= compareValue; //palauttaa true/false
}
// laskee kertoimen prosentista
float getMultiplier(int percent, int potency){
  float base = 1 + (percent * 0.01);  // 1 + (stepSize * 0.01),  esim. 1 + 10(%) * 0.01 = 1.1
  return pow(base, potency);       // base^step,              esim. 1.1² (²=step)
}

// palauttaa true, jos x on suurempi kuin y
bool isValueOverN(int xValue, int yValue){ 
  return xValue > yValue; // palauttaa true/false riippuen lopputuloksesta
}

// palauttaa value / kertoimella ---- esim. 15624 / 1.1 = 14203
int decreaseByPercent(uint16_t value, float multiplier) {
  return value / multiplier;
}