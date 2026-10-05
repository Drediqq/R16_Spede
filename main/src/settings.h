#ifndef SETTINGS_H
#define SETTINGS_H
#include <Arduino.h>

/*
##########################
#### Pelin asetukset #####
##########################
*/
// Score
#define ARR_LEN 5 // max 250

// pelin nopeus
#define STARTSPEED 1 // turha right now, vois mahdollisesti laskea koko ocr1a arvon

#define SPEEDUPVALUE 10 // n% kiihtyvyys
#define SPEEDUPINTERVAL 5 // montako lediä sytytetään kunnes nostetaan vauhtia
#define MAXSPEED 150 // pienempi = nopeampi

// Napit
#define DEBOUNCE_DELAY 70 // 70 on aika hyvä pienille painonapeille9


// asetetaan rekisteri 1 Hz taajuuteen 16 MHz:illä
// 16MHz / (esiskaalaaja * haluttu taajuus)
// (16,000,000 / (1024 * 1)) - 1 = 15624
// jos ocr1a ja prescaler arvon laskee STARTSPEEDistä, sitten näitä ei tarvi
#define OCR1AVALUE 15624 
#define PRESCALER 1024

// show1 ledien syttymisvauhtia muuttava aika millisekunteina
// ledit päällä 2 * LEDBLINKTIME, ja on poissa päältä 1 * LEDBLINKTIME
#define LEDBLINKTIME 200


#endif