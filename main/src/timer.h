#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "logic.h"
#include "settings.h"
#include "helpers.h"

extern volatile bool newTimerInterrupt;
extern uint8_t timerPotency;
extern byte difficulty;

void initializeTimer(void);             // alustaa ja käynnistää timerin
void prescalerHelper(uint16_t scale);  // asettaa prescalerin pyydettyyn arvoon
void timerControl(bool state);        // asettaa ajastimen päälle tai pois syötetyn boolin perusteella
void resetTimer(void);               // asettaa ajastimen 0
void stopTimer(void);               // pysäyttää ajastimen kokonaan asettamalla prescalerin 000
void timerSpeedUp(void);           // nopeuttaa ajastinta
void isItTime(int);               // tarkistetaan pitääkö vauhtia nostaa  ---- vois ehkä kutsua mainloopissa? ----
ISR(TIMER1_COMPA_vect);
#endif
