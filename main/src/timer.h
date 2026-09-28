#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>


extern volatile bool newTimerInterrupt;
extern volatile uint8_t timerCounter;
extern volatile uint8_t timerPotency;


void initializeTimer(void); // alustaa ja käynnistää timerin
void prescalerHelper(uint16_t scale); //asettaa prescalerin pyydettyyn arvoon
void timerControl(bool state);
void resetTimer(void); // asettaa ajastimen 0
void stopTimer(void); // pysäyttää ajastimen kokonaan asettamalla prescalerin 000
void timerSpeedUp(void); // nopeuttaa ajastinta
void isItTime(); // tarkistetaan pitääkö vauhtia nostaa  ---- vois ehkä kutsua mainloopissa? ----
ISR(TIMER1_COMPA_vect); 
#endif
