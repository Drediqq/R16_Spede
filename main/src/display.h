#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include "score.h"
#include "settings.h"

extern byte savedScores[]; // tulostaulukko

// 74HC595:n ohjauspinnit
const int shiftClockPin = 13; // siirtorekisterin kellopinni.
const int latchClockPin = 12; // siirtorekisterin lukituspinni. lukitaan LOW->HIGH siirtymä, jolloin siirtorekisterin sisältö kopioidaan lähtöihin.
const int serialPin = 11; // siirtää dataa sarjamuodossa rekisteriin.


void initializeDisplay(void); // alustetaan siirtorekisterin ohjauspinnit
void writeByte(uint8_t number, bool last);   //Lähetetään valitun numeron segmenttikuvio siirtorekisteriin sarjamuodossa

void writeHighAndLowNumber(uint8_t tens,uint8_t ones); //Kirjoitetaan ensin ykköset ja sitten kymmenet ketjutettuihin siirtorekistereihin
void showResult(byte result);  // Näytetään tulos segmenttinäytöillä
void countDown(byte steps); // lähtölaskenta
void scoreHandler(byte index);// näyttää scoren pyydetystä indeksistä

#endif
