#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//#define SPEEDUPVALUE 10

extern volatile bool newTimerInterrupt;


void initializeTimer(void); // alustaa ja käynnistää timerin
void prescalerHelper(uint16_t); //asettaa prescalerin pyydettyyn arvoon
int percentStepHelper(int, int, int, bool); // laskee n% laskun/korotuksen annettuun arvoon
void resetTimer(void); // asettaa ajastimen 0
void stopTimer(void); // pysäyttää ajastimen kokonaan asettamalla prescalerin 000
void timerSpeedUp(void); // nopeuttaa ajastinta
bool isValueOverN(int value, int maxValue); // tarkistaa onko ajastin pöyrinyt nx
bool isValueUnderN(int value, int maxValue);
int decreaseByPercentage(uint16_t value, float multiplier); // palauttaa 
ISR(TIMER1_COMPA_vect); 
#endif
