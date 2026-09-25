#ifndef SETTINGS_H
#define SETTINGS_H
#include <Arduino.h>

/*
##########################
#### Pelin asetukset #####
##########################
*/

#define STARTSPEED 1 // turha right now, vois mahdollisesti laskea koko ocr1a arvon
#define SPEEDUPVALUE 10 // n% kiihtyvyys

// asetetaan rekisteri 1 Hz taajuuteen 16 MHz:illä
// 16MHz / (esiskaalaaja * haluttu taajuus)
// (16,000,000 / (1024 * 1)) - 1 = 15624
// jos ocr1a ja prescaler arvon laskee STARTSPEEDistä, sitten näitä ei tarvi
#define OCR1AVALUE 15624 
#define PRESCALER 1024



#endif